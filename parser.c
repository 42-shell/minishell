/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:18:56 by jkong             #+#    #+#             */
/*   Updated: 2022/06/17 01:56:37 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_flag.h"
#include "safe_io.h"
#include "string_buffer.h"
#include "generic_list.h"
#include "libft.h"

// S -> list
// simple_command_element -> WORD
// simple_command_element -> redirection
// redirection -> '<' WORD
// redirection -> '>' WORD
// redirection -> '<<' WORD
// redirection -> '>>' WORD
// simple_command -> simple_command_element
// simple_command -> simple_command simple_command_element
// redirection_list -> redirection
// redirection_list -> redirection_list redirection
// command -> simple_command
// command -> subshell
// command -> subshell redirection_list
// subshell -> '(' list ')'
// list -> pipeline
// list -> list '||' pipeline
// list -> list '&&' pipeline
// pipeline -> command
// pipeline -> command '|' pipeline
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
	clear_parser_stack_item(++pst->now);
	pst->now->state = state;
	pst->now->kind = token;
	if (token == TK_WORD)
		swap_word(&pst->now->word, &pst->backup_word);
	return (TK_AGAIN);
}

static t_parser_state	_parse_reduce(t_parser *pst, t_parser_state state)
{
	const t_token_kind	token = (*g_grammer[-state])(pst);

	state = parser_state(pst->now[-1].state, token);
	pst->now->state = state;
	pst->now->kind = token;
	return (state);
}

static void	_parse_on_error(t_parser *pst, t_token_kind token)
{
	t_str_buf	*sb;
	char		*str;

	pst->error = PE_SYNTAX_ERROR;
	sb = NULL;
	sb = str_append(sb, "syntax error near unexpected token `");
	sb = str_append(sb, get_token_str(token));
	sb = str_append(sb, "'\n");
	str = str_dispose(sb);
	puterr_safe(str);
	free(str);
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
			return (1);
		else if (state == PARSER_ERROR)
			_parse_on_error(pst, token);
		else if (state < 0)
			state = _parse_reduce(pst, state);
		else
			token = _parse_shift(pst, state, token);
	}
	return (0);
}
