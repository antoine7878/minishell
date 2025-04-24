/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:54:03 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/02 15:58:16 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(const char *s1, char *s_to_free)
{
	char	*ret;

	ret = ft_strjoin(s1, s_to_free);
	return (gfree(s_to_free), ret);
}

char	*ft_strfreejoin(char *s_to_free, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s_to_free, s2);
	return (gfree(s_to_free), ret);
}

char	*ft_strfreejoinfree(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	return (gfree(s1), gfree(s2), ret);
}
