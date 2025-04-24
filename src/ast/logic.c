/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:00:41 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/27 11:08:08 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_structs.h"
#include "libft.h"

static t_ast	*create_logic(char type, t_ast *first, t_ast *second)
{
	t_ast_logical	*ret;

	ret = gcalloc(1, sizeof(t_ast_logical));
	if (!ret)
		return (ft_mem_err(), NULL);
	ret->type = LOGIC;
	ret->sub_type = type;
	ret->first = first;
	ret->second = second;
	return ((t_ast *)ret);
}

static t_ast	*parse_logic_helper(t_ast *ret, int tok, t_ast *line_ast)
{
	t_ast	*last;

	ret = create_logic(tok, ret, NULL);
	if (!ret)
		return (free_ast(line_ast), free_ast(ret), NULL);
	last = line_ast;
	while (((t_ast_logical *)last)->first->type == LOGIC)
		last = ((t_ast_logical *)last)->first;
	((t_ast_logical *)ret)->second = ((t_ast_logical *)last)->first;
	((t_ast_logical *)last)->first = ret;
	ret = line_ast;
	return (line_ast);
}

t_ast	*parse_logic(t_strm *strm, t_ast *ret, t_ms *ms)
{
	t_ast	*line_ast;
	bool	is_block;
	char	tok;

	if (ms->parsing_error)
		return (free_ast(ret), NULL);
	tok = get_tkn(strm, NULL, 0, ms);
	is_block = peek_tkn(strm, "(");
	line_ast = parse_line(strm, ms);
	if (!line_ast)
		return (free_ast(ret), NULL);
	if (line_ast->type == LOGIC && !is_block)
		ret = parse_logic_helper(ret, tok, line_ast);
	else
		ret = create_logic(tok, ret, line_ast);
	return (ret);
}
