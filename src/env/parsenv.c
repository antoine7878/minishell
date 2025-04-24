/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:08:06 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/20 09:33:15 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "../../include/minishell_structs.h"
#include <stddef.h>
#include <stdlib.h>

t_envp	*parse_env(char **envp)
{
	t_envp	*first;
	t_envp	*last;
	t_envp	*link;
	char	*pos;

	first = gcalloc(1, sizeof(t_envp));
	if (!first)
		return (ft_mem_err(), NULL);
	last = first;
	while (envp && *envp)
	{
		pos = ft_strchr(*envp, '=');
		if (!pos)
			return (ft_mem_err(), NULL);
		last->name = ft_substr(*envp, 0, pos - *envp);
		last->value = ft_strdup(pos + 1);
		last->ptr_ori = *envp;
		link = gcalloc(1, sizeof(t_envp));
		if (!last->value || !last->name || !last || !link)
			return (ft_mem_err(), NULL);
		last->next = link;
		last = last->next;
		envp++;
	}
	return (first);
}

char	**get_envp(t_ms *ms)
{
	size_t	len;
	size_t	i;
	t_envp	*cur;
	char	**ret;

	len = ft_lstsize((t_list *)ms->env);
	ret = galloc((len + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	cur = ms->env;
	i = 0;
	while (cur)
	{
		if (!cur->name)
			return (ret[i] = 0, ret);
		ret[i] = cur->ptr_ori;
		cur = cur->next;
		i++;
	}
	return (NULL);
}
