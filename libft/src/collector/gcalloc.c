/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:35:01 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/12 19:37:07 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <unistd.h>

void	*gcalloc(size_t nmemb, size_t smemb)
{
	void	*ret;

	ret = galloc(nmemb * smemb);
	if (!ret)
	{
		ft_putendl_fd("malloc error", 2);
		rl_clear_history();
		gfree_all();
		write(2, "exit\n", 5);
		exit_child(12);
	}
	ft_bzero(ret, nmemb * smemb);
	return (ret);
}

void	*gcalloc1(size_t nmemb, size_t smemb)
{
	void	*ret;

	ret = galloc(nmemb * smemb);
	if (!ret)
		return (NULL);
	ft_memset(ret, 1, nmemb * smemb);
	return (ret);
}
