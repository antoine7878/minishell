/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:39:35 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/25 12:26:59 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinsert(char *s1, char *s2, size_t start, size_t len)
{
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = gcalloc(s1_len + s2_len - len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s1, start);
	ft_memcpy(ret + start, s2, s2_len);
	ft_memcpy(ret + start + s2_len, s1 + start + len, s1_len - start - len);
	return (ret);
}
