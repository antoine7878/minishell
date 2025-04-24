/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjointab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:36:03 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/27 14:43:31 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stddef.h>

int	ft_tabstrlen(char **strs, char *sep)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (strs[i])
	{
		ret += ft_strlen(strs[i]);
		i++;
	}
	ret += (i - 1) * ft_strlen(sep);
	return (ret);
}

char	*ft_strjointab(char **strs, char *sep)
{
	int		i;
	char	*str;
	int		len;

	if (!*strs)
		return (NULL);
	len = ft_tabstrlen(strs, sep);
	str = galloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	*str = '\0';
	i = 0;
	while (strs[i])
	{
		ft_strcat(str, strs[i]);
		if (strs[i + 1])
			ft_strcat(str, sep);
		i++;
	}
	return (str);
}

char	*ft_strjoinarg(int nb, char *sep, ...)
{
	va_list	ap;
	char	**strs;
	char	*ret;
	int		i;
	int		j;

	strs = gcalloc((nb + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	va_start(ap, sep);
	i = 0;
	j = 0;
	while (j < nb)
	{
		ret = va_arg(ap, char *);
		if (ret)
			strs[i++] = ret;
		j++;
	}
	va_end(ap);
	ret = ft_strjointab(strs, sep);
	gfree(strs);
	return (ret);
}

char	*ft_strjoinargfree(int nb, char *sep, ...)
{
	va_list	ap;
	char	**strs;
	char	*ret;
	int		i;
	int		j;

	strs = gcalloc((nb + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	va_start(ap, sep);
	i = 0;
	j = 0;
	while (j < nb)
	{
		ret = va_arg(ap, char *);
		if (ret)
			strs[i++] = ret;
		j++;
	}
	va_end(ap);
	ret = ft_strjointab(strs, sep);
	free_split(strs);
	return (ret);
}
