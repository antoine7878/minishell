/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:13:47 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/26 13:14:00 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_word(char *s, char *set_end)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_posinset(s[i], set_end) == -1)
		i++;
	return (ft_substr(s, 0, i));
}
