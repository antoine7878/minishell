/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:18:36 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/09 21:18:58 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"

static char	*get_value_name(t_strm *strm, t_ms *ms, size_t i, char **name)
{
	char	*value;

	*name = ft_get_word(strm->str + i + 1, "\"$' \f\t\n\r\v");
	if (**name == '?')
		ft_replace(name, ft_strdup("?"));
	if (*name == NULL)
		return (NULL);
	if (!(**name))
		value = ft_strdup("$");
	else
		value = ft_getenv(*name, ms);
	if (!value)
		value = ft_strdup("");
	return (value);
}

extern int			g_last_status;

char	*expand_env(t_ms *ms, t_strm *strm, bool *was_var)
{
	char	*value;
	char	*name;
	size_t	i;

	i = 0;
	*was_var = (strm->str[i] == '$' && strm->mask[i] == M_NORMAL);
	while (strm->str[i])
	{
		if (strm->str[i] == '$' && strm->mask[i] == M_NORMAL)
		{
			value = get_value_name(strm, ms, i, &name);
			ft_replace(&strm->str, ft_strinsert(strm->str, value, i,
					ft_strlen(name) + 1));
			strm->start = i;
			maskinsert(strm, ft_strlen(name) + 1, ft_strlen(value));
			if (ft_strlen(value) == 0)
				--i;
			gfree(value);
			gfree(name);
		}
		i++;
	}
	return (strm->str);
}
