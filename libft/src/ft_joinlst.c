/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinlst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:37:01 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/09 16:38:23 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_lstjoin_at(t_list *lst, void (*del)(void *), void *(*join)(void *,
			void *))
{
	t_list	*cur_next;
	void	*joined_content;

	if (!lst || !lst->next)
		return (-1);
	cur_next = lst->next;
	joined_content = join(lst->content, cur_next->content);
	if (!joined_content)
		return (-1);
	del(lst->content);
	del(cur_next->content);
	lst->content = joined_content;
	lst->next = cur_next->next;
	gfree(cur_next);
	return (0);
}
