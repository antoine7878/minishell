/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:09:40 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/27 14:09:52 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wildcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (ft_isalnum(s1[i]) && ft_isalnum(s2[i]))
			return (0);
		if (ft_isalnum(s1[i]))
			return (1);
		if (ft_isalnum(s2[i]))
			return (-1);
		i++;
	}
	return (0);
}
