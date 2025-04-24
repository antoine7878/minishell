/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:59:49 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/19 20:25:43 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../include/minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_pwd(char **argv, t_ms *ms)
{
	char	*wd;
	int		error;

	(void)argv;
	(void)ms;
	wd = getcwd(NULL, 0);
	if (!wd)
		return (1);
	error = ft_printf("%s\n", wd);
	free(wd);
	if (error < 0)
		return (1);
	return (0);
}
