/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:11:29 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/20 11:18:04 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"

int	ft_exit(char **argv, t_ms *ms)
{
	size_t	i;

	i = 0;
	(void)ms;
	if (ft_arglen(argv) > 1)
	{
		argv++;
		if (!ft_strcmp(*argv, "--"))
			exit_shell(0);
		if (**argv == '-' || **argv == '+')
			i = 1;
		if (!*(*argv + i) || ft_strany((*argv + i), ft_isndigit))
		{
			ft_dprintf(2, "bash: exit: %s: numeric argument required\n", *argv);
			exit_shell(2);
		}
		if (ft_arglen(argv) > 1)
			return (ft_dprintf(2, "bash: exit: too many arguments\n"), 1);
		exit_shell(ft_atoi(*argv));
	}
	else
		exit_shell(0);
	return (1);
}
