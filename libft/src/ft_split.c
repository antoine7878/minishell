/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:41:35 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/12 23:29:56 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_posinset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_countwords(char const *s, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && ft_posinset(s[i], set) != -1)
			i++;
		if (!s[i])
			return (j);
		while (s[i] && ft_posinset(s[i], set) == -1)
			i++;
		j++;
	}
	return (j);
}

int	ft_wordlen(char const *s, char const *set)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_posinset(s[i], set) == -1)
		i++;
	return (i);
}

void	free_split(char **words)
{
	size_t	i;

	i = 0;
	if (!words)
		return ;
	while (words[i])
	{
		gfree(words[i]);
		words[i++] = NULL;
	}
	if (words)
	{
		gfree(words);
		words = NULL;
	}
}

char	**ft_split(char const *s, char const *set)
{
	size_t	i;
	size_t	j;
	char	**words;
	size_t	wordlen;

	i = 0;
	j = 0;
	words = gcalloc(sizeof(char *), (ft_countwords(s, set) + 1));
	if (!words)
		return (NULL);
	while (s[i])
	{
		while (s[i] && ft_posinset(s[i], set) != -1)
			i++;
		if (s[i])
		{
			wordlen = ft_wordlen(s + i, set);
			words[j] = ft_substr(s, i, wordlen);
			if (!words[j++])
				return (free_split(words), NULL);
			i += wordlen;
		}
	}
	words[j] = 0;
	return (words);
}
