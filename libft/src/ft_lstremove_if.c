/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:55:52 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/09 18:01:56 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_remove_if(t_list **lst, int (*test)(void *), void (*del)(void *))
{
	t_list	*curr;
	t_list	*to_remove;

	curr = *lst;
	while (curr && curr->next)
	{
		if (test(curr->next->content))
		{
			to_remove = curr->next;
			curr->next = curr->next->next;
			del(to_remove->content);
			gfree(to_remove);
		}
		curr = curr->next;
	}
	curr = *lst;
	if (curr && test(curr->content))
	{
		*lst = curr->next;
		del(curr->content);
		gfree(curr);
	}
}

void	ft_lst_remove_ref(t_list **lst, void *ref, int (*cmp)(void *, void *),
		void (*del)(void *))
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
			gfree(to_remove);
		}
		curr = curr->next;
	}
	curr = *lst;
	if (curr && cmp(curr->content, ref) == 0)
	{
		*lst = curr->next;
		del(curr->content);
		gfree(curr);
	}
}
