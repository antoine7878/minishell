/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wild_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:18:05 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/09 21:21:40 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_structs.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>
#include <strings.h>

int	count_slash(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '/')
			i++;
		if (i > 2)
			return (3);
		str++;
	}
	return (i);
}

static bool	is_match_core(char *name, char **needle, bool start, bool end)
{
	char	*match;

	if (!start && *name != **needle)
		return (false);
	if (!*needle && (!*name || end))
		return (true);
	if (*needle == NULL)
		return (false);
	while (1)
	{
		match = ft_strstr(name, *needle);
		if (!match)
			return (false);
		name = match + ft_strlen(*needle);
		if (is_match_core(name, needle + 1, true, end))
			return (true);
	}
}

static bool	is_match(struct dirent *d, char *pattern, bool dir_only,
		bool hidden)
{
	char	**needles;
	bool	ret;

	if (ft_strchr(pattern, '*') == NULL)
		return ((ft_strcmp(d->d_name, pattern) == 0));
	if (!hidden && d->d_name[0] == '.')
		return (false);
	if (d->d_type != DT_DIR && dir_only)
		return (false);
	if (!hidden && (ft_strcmp(d->d_name, ".") == 0 || ft_strcmp(d->d_name,
				"..") == 0))
		return (false);
	needles = ft_split(pattern, "*");
	if (!needles)
		return (NULL);
	ret = is_match_core(d->d_name, needles, pattern[0] == '*',
			pattern[ft_strlen(pattern) - 1] == '*');
	free_split(needles);
	return (ret);
}

static ssize_t	get_dirmatch_count(t_wild *w)
{
	size_t	ret;

	ret = 0;
	w->dir = opendir(w->dir_name);
	if (!w->dir)
		return (-1);
	while (1)
	{
		w->d = readdir(w->dir);
		if (!w->d)
			break ;
		if (is_match(w->d, w->pattern, w->after != NULL, w->pattern[0] == '.'))
			ret++;
	}
	closedir(w->dir);
	return (ret);
}

char	**get_dirmatch(t_wild *w)
{
	char	**ret;
	size_t	j;

	ret = gcalloc(get_dirmatch_count(w) + 1, sizeof(char *));
	w->dir = opendir(w->dir_name);
	if (!w->dir || !ret)
		return (gfree(ret), NULL);
	j = 0;
	while (1)
	{
		w->d = readdir(w->dir);
		if (!w->d)
			break ;
		if (is_match(w->d, w->pattern, w->after != NULL, w->pattern[0] == '.'))
		{
			ret[j] = ft_strdup(w->d->d_name);
			if (!ret[j++])
				return (free_split(ret), closedir(w->dir), NULL);
		}
	}
	closedir(w->dir);
	ft_sort_strs(ret, ft_nstrcmp);
	ft_sort_strs(ret, ft_stricmp);
	ft_sort_strs(ret, ft_wildcmp);
	return (ret);
}
