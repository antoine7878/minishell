/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:43:19 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/15 09:43:23 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

size_t	ft_max_size(size_t a, size_t b)
{
	if (a < b)
		return (b);
	return (a);
}

long	ft_max_l(long a, long b)
{
	if (a < b)
		return (b);
	return (a);
}
