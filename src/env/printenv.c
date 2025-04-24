/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:31:39 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/20 09:31:55 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../include/minishell_structs.h"
#include <stdbool.h>
#include <stddef.h>

int	print_env(t_ms *ms, bool null_flag, char *prefix, char *quote)
{
	t_envp	*cur;

	cur = ms->env;
	while (cur && cur->name)
	{
		if (cur->value)
		{
			if (ft_printf("%s%s=%s%s%s\n", prefix, cur->name, quote, cur->value,
					quote) < 0)
				return (1);
		}
		else if (null_flag)
		{
			if (ft_printf("%s%s\n", prefix, cur->name) < 0)
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}
