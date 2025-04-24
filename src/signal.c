/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:29:19 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/09 10:30:31 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>
#include "libft.h"

extern int	g_last_status;

void	ctrl_c_handler(int a)
{
	(void)a;
	g_last_status = 130;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_c_handler_heredoc(int a)
{
	(void)a;
	g_last_status = 130;
	ft_printf("\n");
	close(0);
}
