/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:11:52 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/02 20:51:39 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_structs.h"

t_ast	*parse_line(t_strm *strm, t_ms *ms)
{
	t_ast	*ret;

	if (ms->parsing_error)
		return (NULL);
	ret = parse_pipe(strm, ms);
	if (!ret)
		return (free_ast(ret), NULL);
	if (*strm->str && peek_tkn(strm, "|&") && *(strm->str + 1) == *strm->str
		&& *(strm->mask + 1) == M_NORMAL)
	{
		ret = parse_logic(strm, ret, ms);
		if (!ret)
			ms->parsing_error = true;
	}
	return (ret);
}
