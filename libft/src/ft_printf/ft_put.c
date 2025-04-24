/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:56:20 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/18 17:34:34 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"
#include <unistd.h>

int	ft_putchar_count_fd(int c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putpad_count_fd(char c, int len, int fd)
{
	int	i;

	i = -1;
	while (++i < len)
		if (ft_putchar_count_fd(c, fd) < 0)
			return (-1);
	return (ft_max(0, len));
}

int	ft_putstr_count_fd(char *str, unsigned int n, int fd)
{
	unsigned int	i;

	i = 0;
	while (str[i] && i < n)
		if (ft_putchar_count_fd(str[i++], fd) < 0)
			return (-1);
	return (i);
}

int	ft_pnbc_fd(long long n, char *base, int fd)
{
	int		base_len;
	int		i;
	int		j;
	char	nbs[25];

	if (n == 0)
		return (ft_putchar_count_fd('0', fd));
	base_len = ft_strlen(base);
	i = 0;
	if (n < 0)
	{
		nbs[i++] = base[-(n % base_len)];
		n = n / base_len;
		n = -n;
	}
	while (n)
	{
		nbs[i++] = base[n % base_len];
		n = n / base_len;
	}
	j = i;
	while (i--)
		if (ft_putchar_count_fd(nbs[i], fd) < 0)
			return (-1);
	return (j);
}

int	ft_punbc_fd(unsigned long long n, char *base, int fd)
{
	unsigned int	base_len;
	int				count;
	int				ret;

	count = 0;
	if (n == 0)
		return (ft_putchar_count_fd('0', fd));
	base_len = ft_strlen(base);
	if (n >= base_len)
	{
		ret = ft_pnbc_fd(n / base_len, base, fd);
		if (ret < 0)
			return (-1);
		count += ret;
	}
	ret = ft_pnbc_fd(n % base_len, base, fd);
	if (ret < 0)
		return (-1);
	count += ret;
	return (count);
}
