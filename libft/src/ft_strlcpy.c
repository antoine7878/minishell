/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:41:37 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/15 09:42:36 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char const *src, size_t size)
{
	size_t	src_len;
	size_t	len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	len = ft_min_size(src_len, size - 1);
	ft_memcpy(dest, src, len);
	dest[len] = '\0';
	return (src_len);
}
