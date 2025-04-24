/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algadea <algadea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:44:10 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/08 17:05:39 by algadea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../include/minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

extern int	g_last_status;

char	*get_heredoc_name(void)
{
	char		*file_name;
	static int	n;

	file_name = ft_itoa(n);
	n++;
	if (!file_name)
		return (NULL);
	return (ft_strjoinfree(".minishell_tmp_", file_name));
}

static int	get_here_doc_helper(char *delimiter, int fd)
{
	static int	line = 0;
	char		*str;
	const char	*p1 = "bash: warning: here-document at line";
	const char	*p2 = "delimited by end-of-file (wanted `";

	line++;
	write(1, "> ", 2);
	str = get_next_line(0);
	if (str == NULL && g_last_status != 130)
		ft_dprintf(2, "%s %i %s%s')\n", p1, line, p2, delimiter);
	if (str == NULL || ft_strcmp(str, delimiter) == '\n')
		return (gfree(str), 1);
	write(fd, str, ft_strlen(str));
	return (gfree(str), 0);
}

int	get_heredoc(char *delimiter, t_ast_redir *redir)
{
	int	fd;

	redir->file_name = get_heredoc_name();
	if (!redir->file_name)
		return (ft_mem_err(), -1);
	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (!fd)
		return (-1);
	while (g_last_status != 130)
	{
		if (get_here_doc_helper(delimiter, fd))
			break ;
	}
	if (g_last_status)
		return (-1);
	return (ft_close(&fd), open(redir->file_name, O_RDONLY, 0600));
}
