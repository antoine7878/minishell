/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:47:15 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/09 11:03:08 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static int	set_pwd_env(t_ms *ms)
{
	char	*pwd;
	char	*newpwd;

	pwd = ft_getenv("PWD", ms);
	if (!pwd)
		return (0);
	ft_setenv(ms, "OLDPWD", pwd);
	gfree(pwd);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (0);
	ft_setenv(ms, "PWD", newpwd);
	free(newpwd);
	return (0);
}

static int	cd_no_args(t_ms *ms)
{
	char	*home;

	home = ft_getenv("HOME", ms);
	if (!home)
		ft_mem_err();
	if (*home == '\0')
		ft_dprintf(2, "bash: cd: HOME not set\n");
	else
	{
		if (chdir(home) < 0)
			return (gfree(home), ft_sys_err(NULL), 1);
		set_pwd_env(ms);
	}
	gfree(home);
	return (0);
}

static int	cd_err(char **argv)
{
	char	*message;

	message = ft_strjoin("cd: ", argv[1]);
	if (!message)
		return (ft_mem_err(), -1);
	ft_sys_err(message);
	gfree(message);
	return (0);
}

static int	cd_dash(t_ms *ms)
{
	char	*oldwd;

	oldwd = ft_getenv("OLDPWD", ms);
	if (!oldwd)
		return (ft_dprintf(2, "bash: cd: OLDPWD not set"), 2);
	if (chdir(oldwd))
		return (gfree(oldwd), 1);
	gfree(oldwd);
	set_pwd_env(ms);
	ft_pwd(NULL, ms);
	return (0);
}

int	ft_cd(char **argv, t_ms *ms)
{
	if (ft_arglen(argv) > 2)
		return (ft_error(ms, "too many arguments"), 1);
	if (ft_arglen(argv) < 2)
		return (cd_no_args(ms));
	if (argv[1] && !ft_strcmp(argv[1], "-"))
		return (cd_dash(ms));
	if (!*argv[1])
		return (0);
	if (chdir(argv[1]))
		return (cd_err(argv), 1);
	set_pwd_env(ms);
	return (0);
}
