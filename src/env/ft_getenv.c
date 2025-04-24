/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:30:50 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/02 21:33:42 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../include/minishell_structs.h"

extern int	g_last_status;

char	*ft_getenv(char *var, t_ms *ms)
{
	t_envp	*cur;

	if (!var)
		return (NULL);
	if (var[0] == '?')
		return (ft_itoa(g_last_status));
	cur = ms->env;
	while (cur && cur->name)
	{
		if (ft_strcmp(cur->name, var) == 0)
		{
			if (!cur->value)
				return (ft_strdup(""));
			return (ft_strdup(cur->value));
		}
		cur = cur->next;
	}
	return (ft_strdup(""));
}
