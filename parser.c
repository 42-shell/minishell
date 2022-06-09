/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:18:56 by jkong             #+#    #+#             */
/*   Updated: 2022/06/09 20:21:07 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_flag.h"
#include "string_buffer.h"
#include "generic_list.h"

#include <stdio.h>

static t_parse_func *const	g_grammer[] = {
	parser_reduce_0,
	parser_reduce_1,
	parser_reduce_2,
	parser_reduce_3,
	parser_reduce_4,
	parser_reduce_5,
	parser_reduce_6,
	parser_reduce_7,
	parser_reduce_8,
	parser_reduce_9,
	parser_reduce_10,
	parser_reduce_11,
	parser_reduce_12,
	parser_reduce_13,
	parser_reduce_14,
	parser_reduce_15,
	parser_reduce_16,
	parser_reduce_17,
	parser_reduce_18,
	parser_reduce_19,
};

static t_token_kind	_parse_shift(t_parser *pst, t_parser_state state,
	t_token_kind token)
{
	pst->now++;
	pst->now->state = state;
	pst->now->kind = token;
	if (token == TK_WORD)
	{
		pst->now->word = pst->backup_word;
		pst->backup_word.str = NULL;
	}
	return (TK_AGAIN);
}

static t_parser_state	_parse_reduce(t_parser *pst, t_parser_state state)
{
	const t_token_kind	token = (*g_grammer[-state])(pst);

	state = parser_state((--pst->now)->state, token);
	_parse_shift(pst, state, token);
	return (state);
}

int	parse(t_parser *pst)
{
	t_parser_state	state;
	t_token_kind	token;

	state = 0;
	token = TK_AGAIN;
	pst->now->state = state;
	pst->now->kind = token;
	while (!pst->error)
	{
		if (token == TK_AGAIN)
			token = read_token(pst);
		if (token == TK_ERROR)
			break ;
		state = parser_state(state, token);
		if (state == PARSER_ACCEPT)
			break ;
		else if (state == PARSER_ERROR)
			pst->error = PE_SYNTAX_ERROR;
		else if (state < 0)
			state = _parse_reduce(pst, state);
		else
			token = _parse_shift(pst, state, token);
	}
	return (0);
}
