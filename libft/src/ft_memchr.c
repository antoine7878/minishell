/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:41:33 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/15 09:42:34 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *s, int c, size_t n)
{
	size_t	i;
	char	*src;
	char	ch;

	src = (char *)s;
	ch = c;
	i = 0;
	while (i < n && src[i] != ch)
		i++;
	if (i < n)
		return ((void *)s + i);
	else
		return (NULL);
}
