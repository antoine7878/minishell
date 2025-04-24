/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:19:40 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/09 21:20:09 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"

int	remove_quotes(t_strm *strm)
{
	size_t	i;
	size_t	j;
	char	*new_str;
	char	*new_mask;

	new_str = gcalloc(ft_strlen(strm->str) + 1, sizeof(char));
	new_mask = gcalloc(ft_strlen(strm->str) + 1, sizeof(char));
	if (!new_str || !new_mask)
		return (gfree(new_mask), gfree(new_str), -1);
	i = 0;
	j = 0;
	while (strm->str[i])
	{
		if (strm->mask[i] == M_VQUOTE)
			i++;
		else
		{
			new_str[j] = strm->str[i];
			new_mask[j++] = strm->mask[i++];
		}
	}
	ft_replace(&strm->str, new_str);
	ft_replace(&strm->mask, new_mask);
	return (0);
}
