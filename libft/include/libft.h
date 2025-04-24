/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:55:02 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/27 14:50:50 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <string.h>

# define BUFFER_SIZE 42
# define FD_MAX 1024

typedef struct s_list
{
	struct s_list	*next;
	void			*content;
}					t_list;

int					ft_isalpha(int c);
int					ft_isnalpha(char c);
int					ft_isdigit(int c);
int					ft_isndigit(char c);
int					ft_isalnum(int c);
int					ft_isnalnum(char c);
int					ft_isalnum(int c);
int					ft_isspace(char c);
int					ft_isnspace(char c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isupper(int c);
int					ft_islower(int c);
size_t				ft_strlen(char const *str);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, void const *src, size_t n);
void				*ft_memmove(void *dest, void const *src, size_t n);
size_t				ft_strlcpy(char *dest, char const *src, size_t size);
size_t				ft_strlcat(char *dest, char const *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(char const *s, int c);
char				*ft_strrchr(char const *s, int c);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
void				*ft_memchr(void const *s, int c, size_t n);
int					ft_memcmp(void const *s1, void const *s2, size_t n);
char				*ft_strnstr(char const *str, char const *to_find,
						size_t len);
char				*ft_strstr(char *str, char *to_find);
int					ft_atoi(char const *nptr);

char				*ft_strdup(char const *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strfreejoinfree(char *s1, char *s2);
char				*ft_strjoinarg(int nb, char *sep, ...);
char				*ft_strjoinargfree(int nb, char *sep, ...);
char				*ft_strtrim(char const *s, char const *set);
char				*ft_strtrimfree(char *s1, char const *set);

char				**ft_split(char const *s, char const *set);
void				print_split(char **tab);
size_t				ft_len_split(char **strs);
void				free_split(char **words);
char				**ft_join_split(char **tab1, char **tab2);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(const char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_sort_strs(char **tab, int (*cmp)(const char *,
							const char *));

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *newlink);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *newlink);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_split_lst(char *s, char c, void (*del)(void *));
void				print_lst(t_list *lst);
t_list				*tab_to_lst(void **tab, void (*del)(void *));
void				ft_lst_remove_if(t_list **lst, int (*test)(void *),
						void (*del)(void *));
int					ft_lstjoin_at(t_list *lst, void (*del)(void *),
						void *(*join)(void *, void *));
void				ft_lst_remove_ref(t_list **lst, void *ref,
						int (*cmp)(void *, void *), void (*del)(void *));
char				*ft_strcat(char *dest, char *src);
void				*gcalloc1(size_t nmemb, size_t smemb);
char				*ft_strcpy(char *dest, char *src);

int					ft_min(int a, int b);
size_t				ft_min_size(size_t a, size_t b);
long				ft_min_l(long a, long b);
int					ft_max(int a, int b);
size_t				ft_max_size(size_t a, size_t b);
long				ft_max_l(long a, long b);
long				ft_abs_l(long nb);
int					ft_abs(int nb);

int					ft_any(int *tab, int len, int (*f)(int));
int					ft_strany(char *str, int (*f)(char));
int					*ft_find(int *tab, int len, int x);
void				ft_striter(char *s, void (*f)(char *));
void				ft_sort_int_tab(int *tab, int size);
void				ft_swap(int *a, int *b);
int					ft_countwords(char const *s, char const *set);
int					ft_wordlen(char const *s, char const *set);
int					ft_posinset(char c, char const *set);

int					ft_printf(const char *fmt, ...);
int					ft_dprintf(int fd, const char *fmt, ...);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_nstrcmp(const char *s1, const char *s2);
int					ft_stricmp(const char *s1, const char *s2);
int					ft_wildcmp(const char *s1, const char *s2);

char				*ft_strjoinfree(const char *s1, char *s_to_free);
char				*ft_strfreejoin(char *s_to_free, const char *s2);

char				*get_next_line(int fd);
void				ft_free(void **ptr);
int					ft_close(int *fd);
int					close_pipe(int fd[2]);
int					close_pipes(int *p1, int p2[2], int p3[2]);
size_t				ft_arglen(char **argv);
char				*ft_strinsert(char *s1, char *s2, size_t start, size_t end);
char				*ft_strjointab(char **strs, char *sep);
int					ft_tabstrlen(char **strs, char *sep);

void				*galloc(size_t size);
void				*gcalloc(size_t nmemb, size_t smemb);
void				gfree_all(void);
void				gfree(void *ptr);
void				ft_replace(char **dest, char *src);
char				*ft_get_word(char *s, char *set_end);

#endif
