/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:45:06 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/08 15:45:23 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"
#include <stddef.h>

bool	is_on_token(t_strm *strm, char *tokens, size_t pos)
{
	if (!tokens || !(*(strm->str + pos)))
		return (false);
	if (ft_strchr(tokens, '&') && *(strm->str + pos) == '&' && *(strm->str + pos
			+ 1) != '&')
		return (false);
	if (!ft_strchr(tokens, *(strm->str + pos)) || *(strm->mask
			+ pos) == M_ESCAPED)
		return (false);
	return (true);
}

bool	peek_tkn(t_strm *strm, char *tokens)
{
	while (*strm->str && ft_strchr(WHITESPACE, *strm->str)
		&& *strm->mask == M_NORMAL)
	{
		strm->mask++;
		strm->str++;
	}
	return (is_on_token(strm, tokens, 0));
}
