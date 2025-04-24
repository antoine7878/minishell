/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:09:34 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/27 11:05:38 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../include/minishell.h"

static t_ast	*create_pipe(t_ast *first, t_ast *second)
{
	t_ast_pipe	*ret;

	ret = gcalloc(1, sizeof(t_ast_pipe));
	if (!ret)
		return (ft_mem_err(), NULL);
	ret->type = PIPE;
	ret->first = first;
	ret->second = second;
	return ((t_ast *)ret);
}

t_ast	*parse_pipe(t_strm *strm, t_ms *ms)
{
	t_ast	*ret;

	if (ms->parsing_error)
		return (NULL);
	ms->error_open = 0;
	ret = parse_exec(strm, ms);
	if (!ret)
		return (free_ast(ret), NULL);
	if (*strm->str && peek_tkn(strm, "|") && *(strm->str + 1) != *strm->str)
	{
		get_tkn(strm, NULL, 0, ms);
		return (create_pipe(ret, parse_pipe(strm, ms)));
	}
	return (ret);
}
