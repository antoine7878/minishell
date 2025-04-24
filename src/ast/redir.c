/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:10:01 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/08 16:11:38 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_structs.h"
#include "libft.h"
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>

static int	get_fd(char *file_name, t_ast_redir *ret, u_int8_t type)
{
	int	here_doc;

	if (type == '>' + 1)
		return (open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644));
	else if (type == '<' + 1)
	{
		signal(SIGINT, ctrl_c_handler_heredoc);
		here_doc = get_heredoc(file_name, ret);
		signal(SIGINT, ctrl_c_handler);
		return (here_doc);
	}
	else if (type == '<')
		return (open(file_name, O_RDONLY, 0644));
	else if (type == '>')
		return (open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	return (-1);
}

t_ast	*create_redir(char type, t_ast *next, t_strm **file_name, t_ms *ms)
{
	t_ast_redir	*ret;
	char		**file;

	ret = gcalloc(1, sizeof(t_ast_redir));
	if (!ret)
		return (ft_mem_err(), NULL);
	ret->type = REDIR;
	ret->next = next;
	ret->std_fd = ((type == '>') || (type == '>' + 1));
	if (ms->error_open)
		return ((t_ast *)ret);
	file = get_argv(file_name, ms);
	if (ft_len_split(file) > 1)
	{
		ret->fd = -1;
		ft_dprintf(2, "bash: %s: ambiguous redirect\n", (*file_name)->str);
		return (free_splitstrm(file_name), ms->error_open = true, (t_ast *)ret);
	}
	ret->fd = get_fd(file[0], ret, type);
	if (type == '<' + 1 && ret->fd < 0 && type != 0)
		return (ms->error_open = true, (t_ast *)ret);
	if (ret->fd < 0 && type != 0)
		return (ft_sys_err(file_name[0]->str), ms->error_open = true,
			(t_ast *)ret);
	return (free_splitstrm(file_name), (t_ast *)ret);
}

t_ast_redir	*redir_al(t_ast_redir *first, t_ast *to_add)
{
	t_ast_redir	*cur;

	if (!to_add)
		return (first);
	if (!first)
		return ((t_ast_redir *)to_add);
	cur = first;
	while (cur->next && cur->type == REDIR)
		cur = (t_ast_redir *)cur->next;
	cur->next = to_add;
	return (first);
}

t_ast	*parse_redir(t_strm *strm, t_ast *ret, t_ms *ms)
{
	char		tok;
	t_strm		**file_name;
	t_ast_redir	*first;

	first = NULL;
	if (ms->parsing_error)
		return (NULL);
	while (*strm->str && peek_tkn(strm, "<>"))
	{
		file_name = NULL;
		tok = get_tkn(strm, NULL, 0, ms);
		if (!*strm->str || peek_tkn(strm, TOKENS))
			return (ms->parsing_error = true, NULL);
		if (get_tkn(strm, &file_name, 1, ms) == 'b')
			return (NULL);
		if (!file_name || !file_name[0])
			return (gfree(file_name), ms->parsing_error = true, NULL);
		first = redir_al(first, create_redir(tok, NULL, file_name, ms));
		if (!first)
			return (free_splitstrm(file_name), NULL);
		gfree(file_name);
	}
	return ((t_ast *)redir_al(first, ret));
}
