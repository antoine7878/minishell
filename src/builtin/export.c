/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 20:44:18 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/19 20:55:02 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"
#include <stddef.h>

static bool	id_err(char *str, bool eq)
{
	if (eq)
		ft_dprintf(2, "bash: export: `=': not a valid identifier\n");
	else
		ft_dprintf(2, "bash: export: `%s': not a valid identifier\n", str);
	return (false);
}

bool	parse_name(char *name)
{
	size_t	i;

	i = 0;
	if (ft_strlen(name) == 0)
		return (false);
	if (ft_isdigit(*name))
		return (false);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	add_env(char **argv, t_ms *ms)
{
	char	*pos;
	char	*name;

	pos = ft_strchr(*argv, '=');
	if (!pos)
	{
		if (!parse_name(*argv))
			return (id_err(*argv, pos));
		return (ft_setenv(ms, *argv, NULL));
	}
	if ((long)ft_strlen(*argv) == pos - *argv)
	{
		if (!parse_name(*argv))
			return (id_err(*argv, pos));
		name = *argv;
		argv++;
		if (*argv)
			return (ft_setenv(ms, name, *argv));
		else
			return (argv--, ft_setenv(ms, name, ""));
	}
	*pos = 0;
	if (!parse_name(*argv))
		return (id_err(*argv, pos));
	return (ft_setenv(ms, *argv, pos + 1));
}

int	ft_export(char **argv, t_ms *ms)
{
	int	ret;

	if (ft_arglen(argv) < 2)
		return (print_env(ms, true, "export ", "\""));
	argv++;
	ret = 0;
	while (*argv)
	{
		if (!add_env(argv++, ms))
			ret = 1;
	}
	return (ret);
}
