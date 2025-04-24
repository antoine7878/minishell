/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:41:31 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/15 09:42:32 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_intlen(int nb)
{
	size_t	ret;

	ret = 1;
	while (nb != 0)
	{
		nb /= 10;
		ret++;
	}
	return (ret - 1);
}

char	*ft_itoa(int n)
{
	char	*ret;
	char	*retn;
	size_t	len;
	int		nb;

	if (n == 0)
		return (ft_strdup("0"));
	nb = n;
	len = ft_intlen(n) - 1;
	ret = gcalloc(sizeof(char), len + 2);
	if (!ret)
		return (ret);
	while (nb != 0)
	{
		ret[len--] = ft_abs(nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
	{
		retn = ft_strjoin("-", ret);
		gfree(ret);
		return (retn);
	}
	return (ret);
}
