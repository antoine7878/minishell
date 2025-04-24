/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:09:02 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/09 21:25:28 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"
#include <stdlib.h>

static t_ast	*create_exec(t_strm **argv)
{
	t_ast_exec	*ret;

	if (!argv)
		return (NULL);
	ret = gcalloc(1, sizeof(t_ast_exec));
	if (!ret)
		return (ft_mem_err(), NULL);
	ret->type = EXEC;
	ret->argv = argv;
	return ((t_ast *)ret);
}

static t_ast_redir	*exec_redir(t_strm *strm, t_strm ***argv, t_ms *ms)
{
	t_ast		*new_redir;
	t_ast_redir	*redir;

	redir = NULL;
	while (peek_tkn(strm, "<>"))
	{
		new_redir = parse_redir(strm, NULL, ms);
		if (ms->parsing_error || !new_redir)
			return (free_ast((t_ast *)redir), NULL);
		redir = redir_al(redir, new_redir);
		get_tkn(strm, argv, -1, ms);
	}
	return (redir);
}

t_ast	*parse_exec(t_strm *strm, t_ms *ms)
{
	t_ast		*exec;
	t_ast_redir	*redir;
	t_strm		**argv;

	if (ms->parsing_error)
		return (NULL);
	argv = NULL;
	exec = NULL;
	if (peek_tkn(strm, "("))
		return (parse_block(strm, ms));
	get_tkn(strm, &argv, -1, ms);
	redir = exec_redir(strm, &argv, ms);
	if (ms->parsing_error)
		return (NULL);
	if (argv)
		exec = create_exec(argv);
	if (exec && redir)
		return ((t_ast *)redir_al(redir, exec));
	else if ((t_ast *)exec)
		return (exec);
	else
		return ((t_ast *)redir);
}
