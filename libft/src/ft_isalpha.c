/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:41:30 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/15 09:42:32 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_islower(int c)
{
	if (('a' <= c && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isupper(int c)
{
	if (('A' <= c && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isnalpha(char c)
{
	return (!ft_isalpha(c));
}
