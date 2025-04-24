/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algadea <algadea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:16:37 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/10 11:22:55 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/include/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int			g_last_status = 0;

static char	*get_prompt(t_ms *ms)
{
	char	*user;
	char	*wd;
	char	*ret;
	char	dollar_color[8];

	if (g_last_status == 0)
		ft_strlcpy(dollar_color, GREEN, 8);
	else
		ft_strlcpy(dollar_color, RED, 8);
	user = ft_getenv("USER", ms);
	wd = getcwd(NULL, 0);
	if (!wd || !user)
		return (free(wd), gfree(user), NULL);
	if (ft_strcmp(user, "") == 0)
		user = ft_strdup("user");
	ret = ft_strjoinarg(10, "", BLUE, user, "@hostname", DEFAULT, ":", GREEN,
			wd, dollar_color, "$ ", DEFAULT);
	gfree(user);
	free(wd);
	return (ret);
}

static int	init_ms(t_ms *ms, char **argv, char **envp)
{
	char	*shlvl;
	int		lvl;

	ft_bzero(ms, sizeof(t_ms));
	ms->argv = argv;
	ms->std_in = -1;
	ms->std_out = -1;
	ms->std_err = -1;
	ms->env = parse_env(envp);
	shlvl = ft_getenv("SHLVL", ms);
	if (!shlvl)
		return (ft_mem_err(), -1);
	lvl = atoi(shlvl);
	gfree(shlvl);
	shlvl = ft_itoa(lvl + 1);
	if (!shlvl)
		return (ft_mem_err(), -1);
	ft_setenv(ms, "SHLVL", shlvl);
	if (!ms->env)
		return (-1);
	return (0);
}

static int	run_line(t_ms *ms, char *line)
{
	t_ast	*ast;
	int		pid;

	if (!line)
		exit_shell(g_last_status);
	if (*line)
	{
		save_stds(ms);
		if (TEST == 0)
			add_history(line);
		ast = parse(&line, ms);
		if (!ast)
			return (restore_stds(ms), -1);
		signal(SIGINT, SIG_IGN);
		pid = run_ast(ast, ms, (int [2]){-1, -1}, (int [2]){-1, -1});
		ft_waitpid(pid, ms);
		free_ast(ast);
		restore_stds(ms);
	}
	return (signal(SIGINT, ctrl_c_handler), 0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_ms	ms;
	char	*prompt;

	if (init_ms(&ms, argv, envp))
		return (gfree_all(), 1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler);
	if (argc > 1)
	{
		run_line(&ms, ft_strjointab(argv + 1, " "));
		exit_shell(g_last_status);
	}
	while (1)
	{
		prompt = get_prompt(&ms);
		if (!prompt)
			ft_mem_err();
		line = readline(prompt);
		gfree(prompt);
		run_line(&ms, line);
		gfree(line);
	}
	return (exit_shell(EXIT_SUCCESS), 0);
}
