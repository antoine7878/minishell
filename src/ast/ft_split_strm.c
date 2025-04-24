/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_strm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algadea <algadea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:41:35 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/09 21:40:50 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_structs.h"
#include "libft.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

static size_t	ft_countwords_strm(t_strm *strm, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (strm->str[i])
	{
		while (strm->str[i] && ft_posinset(strm->str[i], set) != -1
			&& strm->mask[i] != M_ESCAPED)
			i++;
		if (!strm->str[i])
			break ;
		while (strm->str[i] && (ft_posinset(strm->str[i], set) == -1
				|| strm->mask[i] == M_ESCAPED))
			i++;
		j++;
	}
	return (j);
}

static size_t	ft_wordlen_strm(t_strm *strm, size_t pos, char const *set)
{
	size_t	i;

	i = pos;
	while (strm->str[i])
	{
		if (ft_posinset(strm->str[i], set) != -1 && strm->mask[i] != M_ESCAPED)
			break ;
		i++;
	}
	return (i - pos);
}

static t_strm	*substrm(t_strm *strm, size_t start, size_t len)
{
	t_strm	*ret;

	ret = gcalloc(sizeof(t_strm), 1);
	if (!ret)
		return (NULL);
	ret->str = ft_substr(strm->str, start, len);
	ret->mask = ft_substr(strm->mask, start, len);
	return (ret);
}

t_strm	**ft_split_strm(t_strm *strm, char const *set)
{
	size_t	i;
	size_t	j;
	t_strm	**words;
	size_t	wordlen;

	words = gcalloc(sizeof(t_strm *), (ft_countwords_strm(strm, set) + 2));
	if (!words)
		return (ft_mem_err(), NULL);
	i = 0;
	j = 0;
	while (strm->str[i])
	{
		while (strm->str[i] && ft_posinset(strm->str[i], set) != -1
			&& strm->mask[i] != M_ESCAPED)
			i++;
		if (strm->str[i])
		{
			wordlen = ft_wordlen_strm(strm, i, set);
			words[j] = substrm(strm, i, wordlen);
			if (!words[j++])
				return (free_splitstrm(words), ft_mem_err(), NULL);
			i += wordlen;
		}
	}
	return (words);
}
