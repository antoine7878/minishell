/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_strm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:30:31 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/30 16:31:00 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"

void	print_strm(t_strm *strm)
{
	size_t	i;

	ft_putendl_fd(strm->str, 1);
	i = 0;
	while (strm->str[i])
		ft_putchar_fd(strm->mask[i++] + '0', 1);
	ft_putchar_fd('\n', 1);
}
