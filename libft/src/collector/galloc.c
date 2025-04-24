/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   galloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:49:28 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/11 20:47:33 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list			**get_collector(void);

static t_list	*ft_lstnew_collector(void *content)
{
	t_list	*link;

	link = malloc(sizeof(t_list));
	if (!link)
		return (NULL);
	link->content = content;
	link->next = NULL;
	return (link);
}

void	*galloc(size_t size)
{
	void	*block;
	t_list	*link;

	block = malloc(size);
	if (!block)
		return (NULL);
	link = ft_lstnew_collector(block);
	if (!link)
		return (free(block), NULL);
	ft_lstadd_front(get_collector(), link);
	return (block);
}
