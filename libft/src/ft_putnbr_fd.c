/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:41:35 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/15 09:42:35 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (-n > 9)
			ft_putnbr_fd(-(n / 10), fd);
		return (ft_putchar_fd(-(n % 10) + '0', fd));
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}
/*
void	ft_putnbr(int n)
{
	ft_putnbr_fd(n, 1);
}
int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);
	ft_putnbr_fd(atoi(argv[1]), 1);
	ft_putendl_fd("", 1);
	ft_putnbr_fd(atoi(argv[1]), 2);
	ft_putendl_fd("", 2);
	return (0);
}
*/
