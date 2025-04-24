/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_any.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:42:02 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/15 09:42:28 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_any(int *tab, int len, int (*f)(int))
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (f(tab[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_strany(char *str, int (*f)(char))
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (f(str[i]))
			return (1);
		i++;
	}
	return (0);
}
