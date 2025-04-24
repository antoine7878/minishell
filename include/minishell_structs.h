/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algadea <algadea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:45:16 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/08 19:56:03 by algadea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include <dirent.h>
# include <stdbool.h>
# include <sys/types.h>

# define LOGIC 1
# define REDIR 2
# define PIPE 3
# define EXEC 4

# define QUOTES "\'\""
# define TOKENS "<>&|()"
# define WHITESPACE " \n\t"

# define M_NORMAL	1
# define M_ESCAPED	2
# define M_VQUOTE	3

typedef struct s_strm
{
	char			*str;
	char			*mask;
	size_t			start;
}					t_strm;

typedef struct s_envp
{
	struct s_envp	*next;
	char			*name;
	char			*value;
	char			*ptr_ori;
}					t_envp;

typedef struct s_ms
{
	bool			parsing_error;
	char			**argv;
	t_envp			*env;
	bool			is_fork;
	int				std_in;
	int				std_out;
	int				std_err;
	bool			error_open;
}					t_ms;

typedef struct s_wild
{
	char			*dir_name;
	char			*before;
	char			*pattern;
	char			*after;
	DIR				*dir;
	size_t			start_p;
	size_t			end_p;
	struct dirent	*d;
	bool			sort;
}					t_wild;

typedef struct s_ast
{
	u_int8_t		type;
}					t_ast;

typedef struct s_ast_logic
{
	u_int8_t		type;
	char			sub_type;
	struct s_ast	*first;
	struct s_ast	*second;
}					t_ast_logical;

typedef struct s_ast_redir
{
	u_int8_t		type;
	struct s_ast	*next;
	char			std_fd;
	int				fd;
	char			*file_name;
}					t_ast_redir;

typedef struct s_ast_pipe
{
	u_int8_t		type;
	struct s_ast	*first;
	struct s_ast	*second;
}					t_ast_pipe;

typedef struct s_ast_exec
{
	u_int8_t		type;
	t_strm			**argv;
	char			**argvstr;
	char			*exec_path;
	int				status;
}					t_ast_exec;

#endif
