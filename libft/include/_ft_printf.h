/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_printf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:54:34 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/15 09:54:36 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H

# include "libft.h"

# define LEFT -1
# define RIGHT 1

typedef char				t_pos;
typedef unsigned long long	t_ull;

typedef struct s_conv
{
	size_t					width;
	size_t					prec_len;
	t_ull					arg_prim;
	void					*arg_ptr;
	char					sign;
	char					prefix;
	char					pad_char;
	t_pos					pad_pos;
	char					specifier;
	char					is_valid;
	char					end;
	int						conv_len;
}							t_conv;

// parse_convs.c
void						parse_fmt(const char *fmt, va_list *ap,
								t_conv *convs);
// print_convs.c
int							print_conv(t_conv *conv, int fd);

// nbrlen.c
int							ulllen(t_ull nbr, int base_len);
int							ulen(unsigned int nbr, int base_len);
int							ilen(int nbr, int base_len);
//
// conv_ulils.c
t_conv						*create_convs(const char *fmt);
int							nbrlen(t_ull nbr, int base_len);

// ft_puts.c
int							ft_putchar_count_fd(int c, int fd);
int							ft_putpad_count_fd(char c, int len, int fd);
int							ft_putstr_count_fd(char *str, unsigned int n,
								int fd);
int							ft_pnbc_fd(long long n, char *base, int fd);
int							ft_punbc_fd(unsigned long long n, char *base,
								int fd);

#endif
