/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:19:18 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/08 11:19:46 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_close(int *fd)
{
	int	ret;

	if (*fd < 0)
		return (0);
	ret = close(*fd);
	*fd = -1;
	return (ret);
}

int	close_pipe(int p[2])
{
	int	ret1;
	int	ret2;

	ret1 = ft_close(&p[0]);
	ret2 = ft_close(&p[1]);
	if (ret1 < 0 || ret2 < 0)
		return (-1);
	return (0);
}

int	close_pipes(int *p1, int p2[2], int p3[2])
{
	int	ret1;
	int	ret2;
	int	ret3;

	ret1 = 0;
	ret2 = 0;
	ret3 = 0;
	if (p1)
		ret1 = close_pipe(p1);
	if (p2)
		ret2 = close_pipe(p2);
	if (p3)
		ret3 = close_pipe(p3);
	if (ret1 < 0 || ret2 < 0 || ret3 < 0)
		return (-1);
	return (0);
}
