/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:32:12 by ale-tell          #+#    #+#             */
/*   Updated: 2024/11/03 18:20:08 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*create_line(char *buf_tot, char *save, char *find)
{
	size_t	buf_len;
	size_t	len_after;

	buf_len = ft_strlen(buf_tot);
	if (buf_len == 0)
		return (save[0] = '\0', gfree(buf_tot), NULL);
	len_after = ft_strlen(save) - (find - save);
	if (!find || ft_strlen(save) == 0)
		return (save[0] = '\0', buf_tot);
	ft_strlcpy(save, find + 1, len_after);
	buf_tot[buf_len - len_after + 1] = '\0';
	return (buf_tot);
}

static char	*strjoinfree(char *str, char *save)
{
	char	*ret;

	if (!str)
		return (ft_strjoin("", save));
	ret = ft_strjoin(str, save);
	gfree(str);
	return (ret);
}

char	*get_next_line_file(char save[BUFFER_SIZE + 1], int fd)
{
	char	*find;
	char	*buf_tot;
	ssize_t	save_len;

	buf_tot = NULL;
	find = NULL;
	save_len = BUFFER_SIZE;
	while (1)
	{
		buf_tot = strjoinfree(buf_tot, save);
		if (buf_tot == NULL)
			return (save[0] = '\0', NULL);
		find = ft_strchr(save, '\n');
		if (find || save_len < BUFFER_SIZE)
			return (create_line(buf_tot, save, find));
		save_len = read(fd, save, BUFFER_SIZE);
		if (save_len == -1)
			return (save[0] = '\0', gfree(buf_tot), NULL);
		if (save_len == 0 && ft_strlen(buf_tot) == 0)
			return (save[0] = '\0', gfree(buf_tot), NULL);
		save[save_len] = '\0';
	}
}

char	*get_next_line(int fd)
{
	static char	save[BUFFER_SIZE + 1] = {0};

	if (read(fd, NULL, 0) == -1)
		return (save[0] = '\0', NULL);
	return (get_next_line_file(save, fd));
}
