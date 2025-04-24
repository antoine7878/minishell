/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 09:01:58 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/26 14:12:35 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
EXEC:		REDIR {aaa REDIR}
			(BLOCK

REDIR:		{<< WORD}
			{>> WORD}
			{<  WORD}
			{>  WORD}

PIPE:		EXEC [| PIPE]

LINE:		PIPE [&& line]
			PIPE [|| line]

BLOCK:		(LINE) REDIR
*/
