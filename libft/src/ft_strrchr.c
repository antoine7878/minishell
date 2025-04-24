/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:41:44 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/15 09:42:37 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memrchr(void const *s, int c, size_t n)
{
	size_t	i;
	char	*src;
	char	ch;

	src = (char *)s;
	ch = c;
	i = 0;
	if (n == 0)
		return ((void *)s);
	while (i < n && src[n - i - 1] != ch)
		i++;
	if (i < n)
		return ((void *)s + (n - i - 1));
	else
		return (NULL);
}

char	*ft_strrchr(char const *s, int c)
{
	return (ft_memrchr(s, c, ft_strlen(s) + 1));
}
