/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:33:22 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/09 16:33:42 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_lst(t_list *lst)
{
	while (lst)
	{
		ft_printf("<%s>\n", (char *)lst->content);
		lst = lst->next;
	}
}
