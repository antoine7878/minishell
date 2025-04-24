/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:16:01 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/20 14:31:25 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../include/minishell_structs.h"

static void	unset_name(char *name, t_ms *ms)
{
	t_envp	*cur;
	t_envp	*prev;

	prev = NULL;
	cur = ms->env;
	while (cur && cur->name)
	{
		if (ft_strcmp(name, cur->name) == 0)
		{
			gfree(cur->name);
			gfree(cur->value);
			if (prev)
				prev->next = cur->next;
			else
				ms->env = cur->next;
			gfree(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	ft_unset(char **argv, t_ms *ms)
{
	while (*argv)
	{
		unset_name(*argv, ms);
		argv++;
	}
	return (0);
}
