/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:57:03 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/27 13:24:30 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <strings.h>

static void	ft_swap_str(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

void	ft_sort_strs(char **tab, int (*cmp)(const char *, const char *))
{
	int	i;
	int	j;
	int	size;

	size = 0;
	while (tab[size])
		size++;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (cmp(tab[j], tab[j + 1]) > 0)
				ft_swap_str(tab + j, tab + j + 1);
			j++;
		}
		i++;
	}
}
