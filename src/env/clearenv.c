/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:32:43 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/20 09:32:59 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_structs.h"
#include <stdlib.h>

void	ft_envclear(t_envp **env)
{
	t_envp	*l;
	t_envp	*m;

	if (!*env)
		return ;
	l = *env;
	while (l)
	{
		m = l->next;
		free(l->name);
		free(l->value);
		free(l);
		l = m;
	}
	*env = NULL;
}
