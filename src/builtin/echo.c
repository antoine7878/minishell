/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:31:35 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/19 20:28:22 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"
#include <unistd.h>

static bool	parse_flags(char *s)
{
	if (!s)
		return (false);
	if (*s++ != '-')
		return (false);
	if (*s++ != 'n')
		return (false);
	while (*s)
	{
		if (*s++ != 'n')
			return (false);
	}
	return (true);
}

int	ft_echo(char **argv, t_ms *ms)
{
	bool	n;

	(void)ms;
	if (!argv || !*argv)
		return (0);
	argv++;
	n = false;
	while (parse_flags(*argv))
	{
		argv++;
		n = true;
	}
	while (*argv)
	{
		if (write(1, *argv, ft_strlen(*argv)) < 0)
			return (1);
		argv++;
		if (*argv)
			if (write(1, " ", 1) < 0)
				return (1);
	}
	if (!n && write(1, "\n", 1) < 0)
		return (1);
	return (0);
}
