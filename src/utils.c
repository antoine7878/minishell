/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algadea <algadea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:31:10 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/10 11:28:33 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

extern int	g_last_status;

void	exit_child(int code)
{
	rl_clear_history();
	gfree_all();
	exit(code);
}

void	exit_shell(int code)
{
	rl_clear_history();
	gfree_all();
	if (TEST == 0)
		write(2, "exit\n", 5);
	exit(code);
}

void	save_stds(t_ms *ms)
{
	ms->is_fork = 0;
	ms->error_open = false;
	ms->parsing_error = false;
	ms->error_open = false;
	ms->std_in = dup(STDIN_FILENO);
	ms->std_out = dup(STDOUT_FILENO);
	ms->std_err = dup(STDERR_FILENO);
	if (ms->std_in < 0 || ms->std_out < 0 || ms->std_err < 0)
	{
		ft_sys_err(NULL);
		exit_shell(4);
	}
}

void	restore_stds(t_ms *ms)
{
	if (dup2(ms->std_in, STDIN_FILENO) < 0 || dup2(ms->std_out,
			STDOUT_FILENO) < 0 || dup2(ms->std_err, STDERR_FILENO) < 0)
	{
		ft_sys_err(NULL);
		exit_shell(4);
	}
	ft_close(&ms->std_in);
	ft_close(&ms->std_out);
}
