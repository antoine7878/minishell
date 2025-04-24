/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:00:52 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/10 11:21:28 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../include/minishell.h"
#include "../../include/minishell_structs.h"

void	print_argv(char **argv)
{
	while (*argv)
	{
		ft_printf("%s", *argv);
		argv++;
		if (*argv)
			ft_printf(" ", *argv);
	}
}

void	print_indent(int level)
{
	level *= 2;
	while (level--)
		ft_printf(" ");
}

void	print_pipe(t_ast *ast, int level)
{
	print_indent(level);
	ft_printf("(Pipe\n");
	print_indent(level);
	print_ast(((t_ast_pipe *)ast)->first, level + 1);
	print_ast(((t_ast_pipe *)ast)->second, level + 1);
	print_indent(level);
	ft_printf(")\n");
}

void	print_redir(t_ast *ast, int level)
{
	print_indent(level);
	ft_printf("[Redir std_fd: %i, fd: %i\n", ((t_ast_redir *)ast)->std_fd,
		((t_ast_redir *)ast)->fd);
	print_indent(level);
	if (((t_ast_redir *)ast)->next)
		print_ast(((t_ast_redir *)ast)->next, level + 1);
	print_indent(level);
	ft_printf("]\n");
}

void	print_ast(t_ast *ast, int level)
{
	if (!ast)
		return ;
	if (ast->type == EXEC)
	{
		print_indent(level);
		ft_printf("<");
		print_argv(((t_ast_exec *)ast)->argvstr);
		ft_printf(">\n");
	}
	else if (ast->type == PIPE)
		print_pipe(ast, level);
	else if (ast->type == REDIR)
		print_redir(ast, level);
	else if (ast->type == LOGIC)
	{
		print_indent(level);
		ft_printf("{logic type: %c%c\n", ((t_ast_logical *)ast)->sub_type - 1,
			((t_ast_logical *)ast)->sub_type - 1);
		print_ast(((t_ast_logical *)ast)->first, level + 1);
		print_ast(((t_ast_logical *)ast)->second, level + 1);
		print_indent(level);
		ft_printf("}\n");
	}
}
