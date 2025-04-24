/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:10:49 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/26 14:23:44 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*parse_block(t_strm *strm, t_ms *ms)
{
	t_ast	*ret;

	ms->error_open = false;
	if (ms->parsing_error)
		return (NULL);
	if (*strm->str && get_tkn(strm, NULL, 0, ms) != '(')
		return (NULL);
	ret = parse_line(strm, ms);
	if (!ret)
		return (ms->parsing_error = true, free_ast(ret), NULL);
	if (!*strm->str || get_tkn(strm, NULL, 0, ms) != ')')
		return (ms->parsing_error = true, free_ast(ret), NULL);
	return (parse_redir(strm, ret, ms));
}
