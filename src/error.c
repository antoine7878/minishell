/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:19:58 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/27 16:00:45 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "libft.h"
#include <stdio.h>

void	ft_error(t_ms *ms, const char *str)
{
	(void)ms;
	ft_dprintf(2, "%s: %s\n", "bash", str);
}

void	*ft_error_ast(t_ms *ms, const char *str, t_ast *ast)
{
	free_ast(ast);
	ft_error(ms, str);
	return (NULL);
}

void	ft_mem_err(void)
{
	ft_putendl_fd("malloc error", 2);
	exit_child(12);
}

void	ft_sys_err(char *str)
{
	char	*message;

	if (!str)
	{
		perror("bash");
		return ;
	}
	message = ft_strjoin("bash: ", str);
	if (!message)
		ft_mem_err();
	perror(message);
	gfree(message);
}
