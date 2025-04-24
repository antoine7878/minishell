/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_convs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:56:37 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/14 09:56:42 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"

static void	prase_flags(const char **fmt, t_conv *conv)
{
	while (**fmt && ft_strchr("-+ #0", **fmt))
	{
		if (**fmt == '-')
		{
			conv->pad_pos = RIGHT;
			conv->pad_char = ' ';
		}
		if (**fmt == '0' && conv->pad_pos != RIGHT)
		{
			conv->pad_pos = LEFT;
			conv->pad_char = '0';
		}
		if (**fmt == '+')
			conv->sign = '+';
		if (**fmt == ' ' && conv->sign != '+')
			conv->sign = ' ';
		if (**fmt == '#')
			conv->prefix = 1;
		(*fmt)++;
	}
}

static void	parse_flag_width(const char **fmt, va_list *ap, t_conv *conv)
{
	if (**fmt == '*')
	{
		conv->width = va_arg(*ap, unsigned int);
		(*fmt)++;
	}
	else if (**fmt)
	{
		conv->width = ft_atoi(*fmt);
		while (**fmt && ft_isdigit(**fmt))
			(*fmt)++;
	}
}

static char	parse_prec_spec(const char **fmt, va_list *ap, t_conv *conv)
{
	if (**fmt == '.')
	{
		conv->pad_char = ' ';
		(*fmt)++;
		if (**fmt == '*')
		{
			conv->prec_len = va_arg(*ap, unsigned int);
			(*fmt)++;
		}
		else
		{
			conv->prec_len = ft_atoi(*fmt);
			while (**fmt && ft_isdigit(**fmt))
				(*fmt)++;
		}
	}
	if (ft_strchr("sc", **fmt))
		conv->pad_char = ' ';
	if (**fmt == '%')
	{
		conv->width = 0;
		conv->prec_len = 0;
	}
	return (**fmt);
}

static void	get_arg(t_conv *conv, va_list *ap)
{
	if (ft_strchr("idcuxX", conv->specifier))
	{
		conv->arg_prim = va_arg(*ap, long long);
		if (ft_strchr("id", conv->specifier))
		{
			if ((int)conv->arg_prim < 0)
			{
				conv->arg_prim = (int)(-conv->arg_prim);
				conv->sign = '-';
			}
		}
	}
	else if (ft_strchr("sp", conv->specifier))
	{
		conv->arg_ptr = va_arg(*ap, void *);
		if (!conv->arg_ptr)
		{
			conv->specifier = ft_toupper(conv->specifier);
			conv->pad_char = ' ';
		}
	}
	if (!ft_strchr("xX", conv->specifier) || (int)conv->arg_prim == 0)
		conv->prefix = 0;
}

void	parse_fmt(const char *fmt, va_list *ap, t_conv *convs)
{
	const char	*cpy;

	cpy = fmt;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			cpy = fmt;
			fmt++;
			prase_flags(&fmt, convs);
			parse_flag_width(&fmt, ap, convs);
			convs->specifier = parse_prec_spec(&fmt, ap, convs);
			if (!ft_strchr("cspduixX%", convs->specifier))
				convs->is_valid = 0;
			else
			{
				convs->conv_len = fmt - cpy;
				get_arg(convs, ap);
				convs++;
			}
		}
		fmt++;
	}
}
