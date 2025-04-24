/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:09:07 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/27 11:09:19 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	**ft_join_split(char **tab1, char **tab2)
{
	size_t	i;
	size_t	j;
	char	**ret;

	if (!tab1 && !tab2)
		return (NULL);
	if (!tab2)
		return (tab1);
	if (!tab1)
		return (tab2);
	i = 0;
	while (tab1[i])
		i++;
	j = 0;
	while (tab2[j])
		j++;
	ret = gcalloc(i + j + 1, sizeof(char *));
	if (!ret)
		return (gfree(tab1), gfree(tab2), NULL);
	ft_memcpy(ret, tab1, sizeof(char *) * i);
	ft_memcpy(ret + i, tab2, sizeof(char *) * j);
	return (gfree(tab1), gfree(tab2), ret);
}
