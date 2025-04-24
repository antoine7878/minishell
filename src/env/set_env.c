/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:29:22 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/09 11:10:52 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../include/minishell.h"
#include "../../include/minishell_structs.h"

char	*ft_strdup_null(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strdup(str));
}

bool	ft_setenv(t_ms *ms, char *name, char *value)
{
	t_envp	*cur;

	cur = ms->env;
	while (cur && cur->name)
	{
		if (!ft_strcmp(cur->name, name))
		{
			gfree(cur->value);
			cur->value = ft_strdup_null(value);
			return (true);
		}
		cur = cur->next;
	}
	cur->name = ft_strdup(name);
	if (!cur->name)
		return (false);
	cur->value = ft_strdup_null(value);
	if (!cur->value && value)
		return (gfree(cur->name), cur->name = NULL, false);
	cur->ptr_ori = ft_strjoinarg(2, "=", cur->value, cur->name);
	cur->next = gcalloc(1, sizeof(t_envp));
	if (!cur->next)
		return (gfree(cur->value), cur->value = NULL, gfree(cur->name),
			cur->name = NULL, false);
	return (true);
}
