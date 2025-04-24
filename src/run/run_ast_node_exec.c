/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast_node_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:07:51 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/10 11:24:00 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"
#include <sys/wait.h>
#include <unistd.h>

extern int	g_last_status;

static void	run_child(t_ast_exec *exec_node, t_ms *ms, int p_in[2],
		int p_out[2])
{
	if (exec_node->exec_path == NULL)
		exit_child(exec_node->status);
	do_dup(p_in, p_out);
	if (ms->error_open && !g_last_status)
		exit_child(g_last_status);
	if (ms->error_open)
		exit_child(1);
	if (run_builtin(exec_node->argvstr, ms) > -1)
		exit_child(g_last_status);
	run_node(exec_node, ms);
	exit_child(g_last_status);
}

static bool	only_empty_var(t_ast_exec *exec_node, t_ms *ms)
{
	char	*val;
	bool	start_var;

	start_var = false;
	if (exec_node->argv[0]->str[0] == '$' && exec_node->argv[0]->str[1] != 0
		&& exec_node->argv[1] == NULL)
		start_var = true;
	val = ft_getenv(exec_node->argv[0]->str + 1, ms);
	exec_node->argvstr = get_argv(exec_node->argv, ms);
	if (!exec_node->argvstr)
		return (ft_mem_err(), 0);
	if (!exec_node->argvstr[0])
		exec_node->argvstr[0] = ft_strdup("");
	if (!start_var)
		return (false);
	if (!(*val))
		return (gfree(val), true);
	return (gfree(val), false);
}

pid_t	run_exec(t_ast_exec *exec_node, t_ms *ms, int p_in[2], int p_out[2])
{
	pid_t	pid;

	if (only_empty_var(exec_node, ms))
		return (0);
	if (is_builtin(exec_node->argvstr[0]))
		exec_node->exec_path = ft_strdup(exec_node->argvstr[0]);
	else
		exec_node->exec_path = get_path_with_error(ms, exec_node);
	if (!ms->is_fork && !do_dup(p_in, p_out))
	{
		if (ms->error_open && !g_last_status)
			return (g_last_status = 1, 0);
		if (ms->error_open || run_builtin(exec_node->argvstr, ms) >= 0)
			return (0);
	}
	pid = fork();
	if (pid == 0)
		run_child(exec_node, ms, p_in, p_out);
	else if (pid == -1)
		return (ft_sys_err(NULL), 1);
	return (pid);
}
