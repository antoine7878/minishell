/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algadea <algadea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:00:52 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/10 11:16:32 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"
#include "minishell_structs.h"
#include <sys/wait.h>
#include <unistd.h>

extern int	g_last_status;

pid_t	run_pipe(t_ast_pipe *pipe_node, t_ms *ms, int p_in[2], int p_out[2])
{
	int		p[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(p) < 0)
		ft_sys_err(NULL);
	pid1 = fork();
	if (pid1 == 0)
	{
		ms->is_fork = 1;
		ms->error_open = false;
		pid1 = run_ast(pipe_node->first, ms, p_in, p);
		close_pipe(p_in);
		ms->error_open = false;
		pid2 = run_ast(pipe_node->second, ms, p, p_out);
		close_pipes(p_out, p, NULL);
		waitpid(pid1, NULL, 0);
		ft_waitpid(pid2, ms);
		exit_child(g_last_status);
	}
	else if (pid1 == -1)
		ft_sys_err(NULL);
	close_pipes(p_in, p_out, p);
	ft_waitpid(pid1, ms);
	return (0);
}

pid_t	run_redir(t_ast_redir *redir_node, t_ms *ms, int p_in[2], int p_out[2])
{
	int	ret;
	int	*f;

	f = NULL;
	if (redir_node->std_fd == 0)
		f = &p_in[0];
	else if (redir_node->std_fd == 1)
		f = &p_out[1];
	ft_close(f);
	if (!ms->error_open && f)
		*f = redir_node->fd;
	if (redir_node->fd == -1)
		ms->error_open = true;
	if (redir_node->fd == -1 && !g_last_status)
		g_last_status = 1;
	ret = run_ast(redir_node->next, ms, p_in, p_out);
	ft_close(&redir_node->fd);
	return (ret);
}

pid_t	run_logic(t_ast_logical *logic, t_ms *ms, int p_in[2], int p_out[2])
{
	pid_t	pid;

	pid = run_ast(logic->first, ms, p_in, p_out);
	ft_waitpid(pid, ms);
	restore_stds(ms);
	save_stds(ms);
	pid = 0;
	if (logic->sub_type == '&' + 1 && g_last_status == 0)
		pid = run_ast(logic->second, ms, p_in, p_out);
	else if (logic->sub_type == '|' + 1 && g_last_status > 0)
		pid = run_ast(logic->second, ms, p_in, p_out);
	ft_waitpid(pid, ms);
	return (0);
}
