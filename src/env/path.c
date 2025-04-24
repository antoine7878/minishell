/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:48:01 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/09 21:28:56 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern int	g_last_status;

char	**get_paths(t_ms *ms)
{
	char	**paths;
	char	*path_env;
	int		i;

	i = 0;
	path_env = ft_getenv("PATH", ms);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, "=:");
	gfree(path_env);
	if (!paths)
		return (NULL);
	i = 1;
	while (*paths && paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
			paths[i] = ft_strfreejoin(paths[i], "/");
		i++;
	}
	return (paths);
}

static int	path_error(t_ast_exec *exec_node, struct stat *st)
{
	bool	is_path;

	exec_node->status = 127;
	is_path = ft_strchr(exec_node->argvstr[0], '/') != NULL;
	if (access(exec_node->argvstr[0], F_OK) == 0 && (st->st_mode & S_IXUSR) == 0
		&& is_path)
	{
		exec_node->status = 126;
		ft_dprintf(2, "bash: %s: Permission denied\n", exec_node->argvstr[0]);
	}
	else if (is_path && S_ISDIR(st->st_mode) == 1)
	{
		exec_node->status = 126;
		ft_dprintf(2, "bash: %s: Is a directory\n", exec_node->argvstr[0]);
	}
	else if (is_path)
		ft_dprintf(2, "bash: %s: No such file or directory\n",
			exec_node->argvstr[0]);
	else
		ft_dprintf(2, "bash: %s: command not found\n", exec_node->argvstr[0]);
	return (0);
}

static int	get_full_path(t_ms *ms, char **name, struct stat *st, char **full)
{
	char	**paths;

	paths = get_paths(ms);
	if (access(name[0], X_OK) != -1)
		return (stat(name[0], st), *full = ft_strdup(name[0]), 0);
	while (*paths)
	{
		*full = ft_strjoin(*paths, name[0]);
		if (!full)
			return (ft_mem_err(), -1);
		if (access(*full, X_OK) != -1)
			return (stat(*full, st), 0);
		gfree(*full);
		paths++;
	}
	stat(name[0], st);
	return (-1);
}

char	*get_path_with_error(t_ms *ms, t_ast_exec *exec_node)
{
	char		*path;
	struct stat	st;

	ft_memset(&st, 0, sizeof(struct stat));
	path = NULL;
	if (get_full_path(ms, exec_node->argvstr, &st, &path)
		|| S_ISDIR(st.st_mode) == 1 || (st.st_mode & S_IXUSR) == 0)
		return (gfree(path), path_error(exec_node, &st), NULL);
	return (path);
}
