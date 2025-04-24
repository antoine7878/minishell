/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 12:07:51 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/02 21:33:46 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_structs.h"
#include "libft.h"
#include <stddef.h>

static char	is_valid_quote(char *s)
{
	if (*s && *(s + 1) && ft_strchr(QUOTES, *s) && ft_strchr(s + 1, *s))
		return (*s);
	return (0);
}

int	maskinsert(t_strm *strm, size_t len_removed, size_t len_added)
{
	size_t	s1_len;
	size_t	start;
	char	*tmp;
	char	val;

	start = strm->start;
	if (!strm->str)
		return (1);
	tmp = strm->mask;
	s1_len = ft_strlen(strm->str);
	strm->mask = gcalloc(s1_len + 1, sizeof(char));
	if (!strm->mask)
		return (gfree(tmp), 1);
	ft_memcpy(strm->mask, tmp, start);
	val = M_NORMAL;
	if (start > 0 && is_valid_quote(strm->str + start - 1))
		val = M_ESCAPED;
	ft_memset(strm->mask + start, val, len_added);
	ft_memcpy(strm->mask + start + len_added, tmp + start + len_removed, s1_len
		- start - len_added);
	gfree(tmp);
	return (0);
}

void	mask_line(char *line, t_strm *strm)
{
	char	quote;
	size_t	i;

	strm->str = line;
	strm->mask = gcalloc(ft_strlen(line) + 1, sizeof(char));
	i = 0;
	while (line[i])
	{
		strm->mask[i] = M_NORMAL;
		quote = is_valid_quote(line + i);
		if (quote)
		{
			strm->mask[i++] = M_VQUOTE;
			while (line[i] && quote != line[i])
			{
				if (quote == '"' && line[i] == '$')
					strm->mask[i++] = M_NORMAL;
				else
					strm->mask[i++] = M_ESCAPED;
			}
			strm->mask[i++] = M_VQUOTE;
		}
		else
			i++;
	}
}
