/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:41:30 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/15 09:42:32 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	if (ft_strchr("\f\n\t\v\r ", c))
		return (1);
	return (0);
}

int	ft_isnspace(char c)
{
	return (!ft_isspace(c));
}
