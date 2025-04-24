/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wild.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:11:25 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/10 11:08:19 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_structs.h"
#include "libft.h"
#include <dirent.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

char		**get_dirmatch(t_wild *w);

static char	**make_dirmatch(t_wild *w)
{
	char	**matches;
	size_t	i;

	i = -1;
	matches = get_dirmatch(w);
	if (!matches || !*matches)
		return (NULL);
	while (matches[++i])
	{
		matches[i] = ft_strjoinarg(3, "/", w->before, matches[i], w->after);
		if (!matches[i])
			return (free_split(matches), free_split(matches + 1), NULL);
	}
	return (matches);
}

static char	*get_pattern(char *str, t_wild *w)
{
	w->pattern = str;
	if (!ft_strncmp("./", str, 2))
	{
		w->pattern += 2;
		w->before = ".";
	}
	if (str[ft_strlen(str) - 1] == '/')
	{
		str[ft_strlen(str) - 1] = 0;
		w->after = "";
	}
	return (w->pattern);
}

static bool	has_wild(t_strm *strm)
{
	size_t	i;
	char	*first_slash;
	char	*last_slash;

	if (count_slash(strm->str) > 2)
		return (false);
	first_slash = ft_strchr(strm->str, '/');
	last_slash = ft_strrchr(strm->str, '/');
	if (first_slash && first_slash == last_slash)
		if (ft_strncmp("./", strm->str, 2) && strm->str[ft_strlen(strm->str)
				- 1] != '/')
			return (false);
	if (first_slash && first_slash != last_slash && ft_strncmp("./", strm->str,
			2))
		return (false);
	if (last_slash && first_slash != last_slash
		&& strm->str[ft_strlen(strm->str) - 1] != '/')
		return (false);
	i = -1;
	while (strm->str[++i])
		if (strm->str[i] == '*' && strm->mask[i] == M_NORMAL)
			return (true);
	return (false);
}

char	**replace_wild(t_strm *strm)
{
	t_wild	w;
	char	**ret;

	ft_memset(&w, 0, sizeof(t_wild));
	w.pattern = get_pattern(strm->str, &w);
	if (!w.pattern)
		return (NULL);
	w.dir_name = ".";
	ret = make_dirmatch(&w);
	gfree(&w);
	return (ret);
}

char	**expand_wild(t_strm *strm)
{
	char	**ret;
	char	*save;

	save = ft_strdup(strm->str);
	if (!save)
		return (ft_mem_err(), NULL);
	if (!has_wild(strm))
	{
		ret = gcalloc(2, sizeof(char *));
		ret[0] = strm->str;
		return (ret);
	}
	ret = replace_wild(strm);
	if (!ret)
	{
		ret = gcalloc(2, sizeof(char *));
		if (!ret)
			return (ft_mem_err(), NULL);
		ret[0] = save;
		return (ret);
	}
	gfree(save);
	gfree(strm->str);
	gfree(strm->mask);
	return (ret);
}
