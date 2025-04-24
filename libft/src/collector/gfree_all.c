/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfree_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:49:28 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/11 20:46:02 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	**get_collector(void);

void	gfree_all(void)
{
	t_list	**collector;
	t_list	*cur;
	t_list	*nxt;

	collector = get_collector();
	cur = *collector;
	while (cur)
	{
		free(cur->content);
		nxt = cur->next;
		free(cur);
		cur = nxt;
	}
	*collector = NULL;
}
