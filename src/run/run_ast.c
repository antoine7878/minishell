/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:00:52 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/09 21:26:12 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_structs.h"
#include "libft.h"
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern int	g_last_status;

int	run_ast(t_ast *ast, t_ms *ms, int p_in[2], int p_out[2])
{
	int	ret;

	ret = 1;
	if (!ast)
		return (0);
	if (ast->type == EXEC)
		ret = run_exec((t_ast_exec *)ast, ms, p_in, p_out);
	else if (ast->type == PIPE)
		ret = run_pipe((t_ast_pipe *)ast, ms, p_in, p_out);
	else if (ast->type == REDIR)
		ret = run_redir((t_ast_redir *)ast, ms, p_in, p_out);
	else if (ast->type == LOGIC)
		ret = run_logic((t_ast_logical *)ast, ms, p_in, p_out);
	return (ret);
}

int	run_builtin(char **argv, t_ms *ms)
{
	int	code;

	code = -1;
	if (ft_strcmp(argv[0], "echo") == 0)
		code = ft_echo(argv, ms);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		code = ft_pwd(argv, ms);
	else if (ft_strcmp(argv[0], "cd") == 0)
		code = ft_cd(argv, ms);
	else if (ft_strcmp(argv[0], "env") == 0)
		code = ft_env(argv, ms);
	else if (ft_strcmp(argv[0], "export") == 0)
		code = ft_export(argv, ms);
	else if (ft_strcmp(argv[0], "unset") == 0)
		code = ft_unset(argv, ms);
	else if (ft_strcmp(argv[0], "exit") == 0)
		code = ft_exit(argv, ms);
	if (code != -1)
		g_last_status = code;
	return (code);
}

bool	is_builtin(char *name)
{
	if (ft_strcmp(name, "echo") == 0)
		return (true);
	else if (ft_strcmp(name, "pwd") == 0)
		return (true);
	else if (ft_strcmp(name, "cd") == 0)
		return (true);
	else if (ft_strcmp(name, "env") == 0)
		return (true);
	else if (ft_strcmp(name, "export") == 0)
		return (true);
	else if (ft_strcmp(name, "unset") == 0)
		return (true);
	else if (ft_strcmp(name, "exit") == 0)
		return (true);
	return (false);
}
