/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:49:28 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/11 20:47:40 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		**get_collector(void);

static int	find(void *v1, void *v2)
{
	if (v1 == v2)
		return (0);
	return (1);
}

static void	ft_lst_remove_ref_col(t_list **lst, void *ref, int (*cmp)(void *,
			void *), void (*del)(void *))
{
	t_list	*curr;
	t_list	*to_remove;

	curr = *lst;
	while (curr && curr->next)
	{
		if (cmp(curr->next->content, ref) == 0)
		{
			to_remove = curr->next;
			curr->next = curr->next->next;
			del(to_remove->content);
			free(to_remove);
		}
		curr = curr->next;
	}
	curr = *lst;
	if (curr && cmp(curr->content, ref) == 0)
	{
		*lst = curr->next;
		del(curr->content);
		free(curr);
	}
}

void	gfree(void *ptr)
{
	if (ptr)
		ft_lst_remove_ref_col(get_collector(), ptr, find, free);
}
