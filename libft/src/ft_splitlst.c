/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:33:59 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/09 16:34:35 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_split_lst(char *s, char c, void (*del)(void *))
{
	t_list	*ret;
	t_list	*current;
	char	*temp;

	ret = ft_lstnew(NULL);
	if (!ret)
		return (NULL);
	current = ret;
	while (1)
	{
		temp = ft_strchr(s, c);
		if (temp)
			current->content = ft_substr(s, 0, temp - s);
		else
			current->content = ft_substr(s, 0, -1);
		if (!temp)
			break ;
		s = temp + 1;
		current->next = ft_lstnew(NULL);
		if (!current->content || !current->next)
			return (ft_lstclear(&ret, del), NULL);
		current = current->next;
	}
	return (ret);
}
