/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:18:56 by jkong             #+#    #+#             */
/*   Updated: 2022/05/26 18:14:55 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_flag.h"
#include "string_buffer.h"

#include <stdio.h>

void	lex(t_parse_state *pst)
{
	t_token_kind	token;

	token = TK_AGAIN;
	while (token != TK_EOF)
	{
		if (token != TK_AGAIN)
		{
			//code
			if (token != TK_WORD)
				printf("[DEBUG] Token \'%c\' (%d)\n", token, token);
			else
				printf("[DEBUG] WORD [\"%s\"]\n", pst->now_word.str);
		}
		token = read_token(pst);
	}
}
