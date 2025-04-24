/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:21:26 by ale-tell          #+#    #+#             */
/*   Updated: 2025/01/09 21:26:24 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_structs.h"
# include <stdbool.h>
# include <stddef.h>
# include <sys/stat.h>

/*		TEXT FORMATING		*/
# define DEFAULT "\001\033[0m\002"
# define BOLD "\001\033[1m\002"
# define ITALIC "\001\033[3m\002"

# define BLACK "\001\033[30m\002"
# define RED "\001\033[31m\002"
# define GREEN "\001\033[32m\002"
# define YELLOW "\001\033[33m\002"
# define BLUE "\001\033[34m\002"
# define MAGENTA "\001\033[35m\002"
# define CYAN "\001\033[36m\002"
# define WHITE "\001\033[37m\002"

# ifndef TEST
#  define TEST 0
# endif

char		**expand_wild(t_strm *strm);
char		*expand_env(t_ms *ms, t_strm *strm, bool *was_var);
char		**get_argv(t_strm **strms, t_ms *ms);
char		*ft_strdup_null(char *str);
t_strm		**ft_split_strm(t_strm *strm, char const *set);
int			remove_quotes(t_strm *strm);
char		**replace_wild(t_strm *strm);
void		free_splitstrm(t_strm **strms);
void		free_strm(t_strm *strm);
void		free_splitstrm(t_strm **strms);
int			count_slash(char *str);
bool		is_builtin(char *name);

// parse
t_ast		*parse(char **line, t_ms *ms);
void		print_strm(t_strm *strm);
void		mask_line(char *line, t_strm *strm);
int			maskinsert(t_strm *strm, size_t len_removed, size_t len_added);
void		free_strm(t_strm *strm);

// ast
bool		is_on_token(t_strm *strm, char *tokens, size_t pos);
bool		peek_tkn(t_strm *strm, char *tokens);
int			get_tkn(t_strm *strm, t_strm ***words, int count, t_ms *ms);

t_ast		*parse_line(t_strm *strm, t_ms *ms);
t_ast		*parse_pipe(t_strm *strm, t_ms *ms);
t_ast		*parse_exec(t_strm *strm, t_ms *ms);
t_ast		*parse_block(t_strm *strm, t_ms *ms);
t_ast		*parse_logic(t_strm *strm, t_ast *ret, t_ms *ms);
t_ast		*parse_redir(t_strm *strm, t_ast *ret, t_ms *ms);
t_ast_redir	*redir_al(t_ast_redir *first, t_ast *to_add);

// error
void		ft_error(t_ms *ms, const char *str);
void		*ft_error_ast(t_ms *ms, const char *str, t_ast *ast);
void		ft_mem_err(void);
void		ft_sys_err(char *str);

// utils
void		exit_shell(int code);
void		exit_child(int code);
void		save_stds(t_ms *ms);
void		restore_stds(t_ms *ms);

// signals
void		ctrl_c_handler(int a);
void		ctrl_c_handler_heredoc(int a);

char		**get_paths(t_ms *ms);
char		*get_path_with_error(t_ms *ms, t_ast_exec *exec_node);

void		print_ast(t_ast *ast, int level);
void		free_ast(t_ast *ast);

int			run_exec(t_ast_exec *exec_node, t_ms *ms, int p_in[2],
				int p_out[2]);
int			run_pipe(t_ast_pipe *pipe_node, t_ms *ms, int p_in[2],
				int p_out[2]);
int			run_redir(t_ast_redir *redir_node, t_ms *ms, int p_in[2],
				int p_out[2]);
int			run_logic(t_ast_logical *logic, t_ms *ms, int p_in[2],
				int p_out[2]);
int			run_ast(t_ast *ast, t_ms *ms, int p_in[2], int p_out[2]);

int			ft_waitpid(pid_t pid, t_ms *ms);
int			ft_dup2(int fd1, int fd2);
int			do_dup(int p_in[2], int p_out[2]);
int			run_node(t_ast_exec *exec_node, t_ms *ms);

void		ft_envclear(t_envp **env);
char		*ft_getenv(char *var, t_ms *ms);
t_envp		*parse_env(char **envp);
char		**get_envp(t_ms *ms);
int			print_env(t_ms *ms, bool null_flag, char *prefix, char *quote);
bool		ft_setenv(t_ms *ms, char *name, char *value);

int			get_heredoc(char *delimiter, t_ast_redir *redir);

int			run_builtin(char **argv, t_ms *ms);
int			ft_echo(char **argv, t_ms *ms);
int			ft_pwd(char **argv, t_ms *ms);
int			ft_cd(char **argv, t_ms *ms);
int			ft_env(char **argv, t_ms *ms);
int			ft_export(char **argv, t_ms *ms);
int			ft_exit(char **argv, t_ms *ms);
int			ft_unset(char **argv, t_ms *ms);

#endif
