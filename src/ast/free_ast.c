/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:00:52 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/10 11:21:32 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../include/minishell.h"
#include "../../include/minishell_structs.h"
#include <unistd.h>

static void	free_redir(t_ast_redir *redir)
{
	if (redir->next)
		free_ast(redir->next);
	ft_close(&redir->fd);
	if (redir->file_name)
		unlink(redir->file_name);
	gfree(redir->file_name);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == EXEC)
	{
		free_splitstrm(((t_ast_exec *)ast)->argv);
		free_split(((t_ast_exec *)ast)->argvstr);
		gfree(((t_ast_exec *)ast)->exec_path);
	}
	else if (ast->type == PIPE)
	{
		free_ast(((t_ast_pipe *)ast)->first);
		free_ast(((t_ast_pipe *)ast)->second);
	}
	else if (ast->type == REDIR)
		free_redir((t_ast_redir *)ast);
	else if (ast->type == LOGIC)
	{
		free_ast(((t_ast_logical *)ast)->first);
		free_ast(((t_ast_logical *)ast)->second);
	}
	gfree(ast);
}
