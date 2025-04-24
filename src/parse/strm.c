/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:17:17 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/10 11:23:42 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"
#include "minishell_structs.h"
#include <stddef.h>
#include <string.h>

void	free_strm(t_strm *strm)
{
	gfree(strm->str);
	gfree(strm->mask);
}

void	free_splitstrm(t_strm **strms)
{
	size_t	i;

	i = 0;
	while (strms[i])
		free_strm(strms[i++]);
	gfree(strms);
}

t_strm	*make_strm(void)
{
	t_strm	*ret;

	ret = gcalloc(1, sizeof(t_strm));
	if (!ret)
		return (ft_mem_err(), NULL);
	ret->str = ft_strdup("");
	ret->mask = ft_strdup("");
	return (ret);
}

static void	get_argv_loop(t_strm *strm, t_ms *ms, char ***ret)
{
	char	**exp;
	size_t	j;
	t_strm	**s;
	bool	was_var;

	expand_env(ms, strm, &was_var);
	remove_quotes(strm);
	s = ft_split_strm(strm, WHITESPACE);
	if (!s)
	{
		gfree(*ret);
		return ;
	}
	j = -1;
	if (!(*s) && !was_var)
		ft_replace((char **)s, (char *)make_strm());
	while (s[++j])
	{
		exp = expand_wild(s[j]);
		*ret = ft_join_split(*ret, exp);
	}
}

char	**get_argv(t_strm **strms, t_ms *ms)
{
	char	**ret;
	size_t	i;

	ret = gcalloc(2, sizeof(char *));
	if (!ret)
		return (ft_mem_err(), NULL);
	i = -1;
	while (strms[++i])
		get_argv_loop(strms[i], ms, &ret);
	return (ret);
}
