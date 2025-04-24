/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabtlst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:30:57 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/09 16:31:40 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

t_list	*tab_to_lst(void **tab, void (*del)(void *))
{
	t_list	*ret;
	t_list	*current;
	size_t	i;

	ret = ft_lstnew(tab[0]);
	if (!ret)
		return (NULL);
	i = 1;
	current = ret;
	while (tab[i])
	{
		current->next = ft_lstnew(tab[i++]);
		if (!current->next)
			return (ft_lstclear(&ret, del), NULL);
		current = current->next;
	}
	gfree(tab);
	return (ret);
}
