/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:12:41 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/09 21:40:52 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_structs.h"
#include "libft.h"
#include <stddef.h>

static char	get_double_token(t_strm *strm)
{
	int	ret;

	ret = *strm->str;
	strm->mask++;
	strm->str++;
	if (*strm->str == *(strm->str - 1))
	{
		strm->str++;
		strm->mask++;
		ret++;
	}
	return (ret);
}

static size_t	get_word_token_helper(t_strm *strm, bool is_file)
{
	size_t	i;

	i = 0;
	while (strm->str[i] && !(is_on_token(strm, TOKENS, i)))
	{
		if (is_file && ft_posinset(strm->str[i], WHITESPACE) != -1
			&& strm->str[i - 1]
			&& ft_posinset(strm->str[i - 1], WHITESPACE) == -1
			&& strm->mask[i] != M_ESCAPED)
			break ;
		i++;
	}
	return (i);
}

static char	get_word_token(t_strm *strm, t_strm ***words, bool is_file)
{
	size_t	i;
	t_strm	**word;
	char	tmp;

	i = get_word_token_helper(strm, is_file);
	tmp = strm->str[i];
	strm->str[i] = 0;
	word = ft_split_strm(strm, WHITESPACE);
	*words = (t_strm **)ft_join_split((char **)*words, (char **)word);
	if (!(*words) || !word)
		return (ft_mem_err(), 0);
	strm->str[i] = tmp;
	strm->str += i;
	strm->mask += i;
	return ('a');
}

int	get_tkn(t_strm *strm, t_strm ***words, int count, t_ms *ms)
{
	int	ret;

	(void)ms;
	if (peek_tkn(strm, TOKENS) && count)
		return (0);
	if (!*strm->str)
		return (0);
	ret = *strm->str;
	if (ft_strchr("()", *strm->str))
	{
		strm->mask++;
		strm->str++;
	}
	else if (ft_strchr("<>|", *strm->str) || ft_strncmp(strm->str, "&&",
			2) == 0)
		ret = get_double_token(strm);
	else
		ret = get_word_token(strm, words, count == 1);
	peek_tkn(strm, NULL);
	return (ret);
}
