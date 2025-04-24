/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algadea <algadea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:54:47 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/08 16:40:46 by algadea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

extern int	g_last_status;

int	ft_waitpid(pid_t pid, t_ms *ms)
{
	int	status;

	(void)ms;
	if (!pid)
		return (0);
	if (waitpid(pid, &status, WUNTRACED) < 0)
		return (ft_sys_err(NULL), -1);
	if (WIFEXITED(status))
		g_last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_status = 128 + WTERMSIG(status);
	else if (WIFSTOPPED(status))
		g_last_status = 128 + WSTOPSIG(status);
	else
		g_last_status = 1;
	return (0);
}

int	ft_dup2(int fd1, int fd2)
{
	if (fd1 < 0 && fd2 < 0)
		return (0);
	if (fd1 < 0 || fd2 < 0)
		return (0);
	return (dup2(fd1, fd2));
}

int	do_dup(int p_in[2], int p_out[2])
{
	ft_dup2(p_in[0], 0);
	ft_dup2(p_out[1], 1);
	close_pipe(p_in);
	close_pipe(p_out);
	return (0);
}

int	run_node(t_ast_exec *exec_node, t_ms *ms)
{
	char	**envp;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	envp = get_envp(ms);
	if (!envp)
		return (free_split(envp), ft_mem_err(), -1);
	execve(exec_node->exec_path, exec_node->argvstr, envp);
	free_split(envp);
	g_last_status = 127;
	ft_error(ms, NULL);
	return (-1);
}
