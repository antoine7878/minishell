/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:59:07 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/20 09:03:48 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../include/minishell.h"
#include <stdbool.h>

int	ft_env(char **argv, t_ms *ms)
{
	if (ft_arglen(argv) > 1)
		return (ft_error(ms, "too many arguments"), 1);
	return (print_env(ms, false, "", ""));
}
