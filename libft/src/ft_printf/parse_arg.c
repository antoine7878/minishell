/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:56:31 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/14 09:56:42 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"

static int	is_zero(t_conv *conv)
{
	if (conv->prec_len != 0)
		return (0);
	if (ft_strchr("uxX", conv->specifier))
		return ((unsigned int)conv->arg_prim == 0);
	if (ft_strchr("id", conv->specifier))
		return ((int)conv->arg_prim == 0);
	return (0);
}

static int	print_arg(t_conv *conv, int fd)
{
	if (ft_strchr("duixX", conv->specifier) && is_zero(conv))
		return (0);
	if (conv->specifier == 'c')
		return (ft_putchar_count_fd((char)conv->arg_prim, fd));
	else if (ft_strchr("di", conv->specifier))
		return (ft_pnbc_fd((int)conv->arg_prim, "0123456789", fd));
	else if (conv->specifier == 'u')
		return (ft_punbc_fd((unsigned int)conv->arg_prim, "0123456789", fd));
	else if (conv->specifier == 'x')
		return (ft_punbc_fd((unsigned int)conv->arg_prim, "0123456789abcdef",
				fd));
	else if (conv->specifier == 'X')
		return (ft_punbc_fd((unsigned int)conv->arg_prim, "0123456789ABCDEF",
				fd));
	else if (conv->specifier == '%')
		return (ft_putchar_count_fd('%', fd));
	else if (conv->specifier == 's' && conv->arg_ptr)
		return (ft_putstr_count_fd((char *)conv->arg_ptr, conv->prec_len, fd));
	else if (conv->specifier == 'S' && !conv->arg_ptr && conv->prec_len > 5)
		return (ft_putstr_count_fd("(null)", -1, fd));
	else if (conv->specifier == 'p' && conv->arg_ptr)
		return (ft_punbc_fd((t_ull)conv->arg_ptr, "0123456789abcdef", fd));
	else if (conv->specifier == 'P' && !conv->arg_ptr)
		return (ft_putstr_count_fd("(nil)", -1, fd));
	return (0);
}

static int	arglen(t_conv *conv)
{
	if (ft_strchr("duixX", conv->specifier) && is_zero(conv))
		return (0);
	else if (ft_strchr("u", conv->specifier))
		return (ulen(conv->arg_prim, 10));
	else if (ft_strchr("id", conv->specifier))
		return (ilen(conv->arg_prim, 10));
	else if (ft_strchr("xX", conv->specifier))
		return (ulen(conv->arg_prim, 16));
	else if (conv->specifier == 'p')
		return (ulllen((t_ull)conv->arg_ptr, 16));
	else if (conv->specifier == 's')
		return (ft_min_size(conv->prec_len, ft_strlen((char *)conv->arg_ptr)));
	else if (conv->specifier == 'S' && conv->prec_len > 5)
		return (6);
	else if (conv->specifier == 'S' && conv->prec_len <= 5)
		return (0);
	else if (conv->specifier == 'P')
		return (5);
	else if (conv->specifier == '%')
		return (1);
	else if (conv->specifier == 'c')
		return (1);
	return (0);
}

static int	get_paddindlen(t_conv *conv)
{
	if (ft_strchr("sPSc", conv->specifier))
		return (conv->width - arglen(conv) - 2 * (conv->prefix != 0) - 2
			* (conv->specifier == 'p'));
	return (conv->width - ft_max(arglen(conv), conv->prec_len)
		- (conv->sign != 0 && ft_strchr("dpi", conv->specifier)) - 2
		* (conv->prefix != 0) - 2 * (conv->specifier == 'p'));
}

int	print_conv(t_conv *conv, int fd)
{
	int	count;
	int	padding_len;

	count = 0;
	padding_len = get_paddindlen(conv);
	if (padding_len > 0 && conv->pad_char == ' ' && conv->pad_pos == LEFT)
		count += ft_putpad_count_fd(conv->pad_char, padding_len, fd);
	if (conv->sign && ft_strchr("dpi", conv->specifier))
		count += ft_putchar_count_fd(conv->sign, fd);
	if ((conv->specifier == 'p') || (conv->prefix && conv->specifier == 'x'
			&& conv->arg_prim != 0))
		count += ft_putstr_count_fd("0x", -1, fd);
	if (conv->prefix && conv->specifier == 'X' && conv->arg_prim != 0)
		count += ft_putstr_count_fd("0X", -1, fd);
	if (conv->prec_len && ft_strchr("pduixX", conv->specifier))
		count += ft_putpad_count_fd('0', conv->prec_len - arglen(conv), fd);
	if (padding_len > 0 && conv->pad_char == '0' && conv->pad_pos == LEFT)
		count += ft_putpad_count_fd(conv->pad_char, padding_len, fd);
	count += print_arg(conv, fd);
	if (padding_len > 0 && conv->pad_char == ' ' && conv->pad_pos == RIGHT)
		count += ft_putpad_count_fd(conv->pad_char, padding_len, fd);
	return (count);
}
