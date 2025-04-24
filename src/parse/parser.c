/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algadea <algadea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:45:14 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/09 21:20:52 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"

extern int	g_last_status;

t_ast	*parse(char **line, t_ms *ms)
{
	t_ast	*ret;
	t_strm	strm;

	ret = NULL;
	mask_line(*line, &strm);
	if (strm.str[0] == 0)
		return (NULL);
	ret = parse_line(&strm, ms);
	gfree(strm.mask);
	if (ms->parsing_error || *strm.str)
	{
		g_last_status = 2;
		ft_dprintf(2, "bash: syntax error near unexpected token `");
		if (!*strm.str || *strm.str == '\n')
			ft_dprintf(2, "newline'\n");
		else if (*strm.str && *strm.str == *(strm.str + 1))
			ft_dprintf(2, "%c%c'\n", *strm.str, *(strm.str + 1));
		else
			ft_dprintf(2, "%c'\n", *strm.str);
	}
	return (ret);
}
