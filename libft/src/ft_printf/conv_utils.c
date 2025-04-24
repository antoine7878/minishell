/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:56:03 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/14 09:56:42 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"
#include <stdlib.h>

static size_t	count_conv(const char *fmt)
{
	size_t	ret;

	ret = 0;
	while (*fmt)
	{
		if (*fmt == '%' && *(fmt + 1) != '%')
			ret++;
		if (*fmt == '%' && *(fmt + 1) == '%')
		{
			ret++;
			fmt++;
		}
		fmt++;
	}
	return (ret);
}

t_conv	*create_convs(const char *fmt)
{
	t_conv	*convs;
	int		size;
	int		i;

	size = count_conv(fmt);
	convs = (t_conv *)galloc(sizeof(t_conv) * (size + 1));
	if (!convs)
		return (NULL);
	convs[size].end = 0;
	i = 0;
	while (i < size)
	{
		convs[i].arg_prim = 0;
		convs[i].arg_ptr = NULL;
		convs[i].prec_len = -1;
		convs[i].sign = 0;
		convs[i].prefix = 0;
		convs[i].pad_char = ' ';
		convs[i].pad_pos = LEFT;
		convs[i].specifier = 0;
		convs[i].is_valid = 1;
		convs[i].end = 1;
		i++;
	}
	return (convs);
}
