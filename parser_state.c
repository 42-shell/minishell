/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/06/09 18:18:37 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const t_state_info			g_parser_state_0[] = {
	(t_state_info){TK_WORD, 8},
	(t_state_info){TK_LESS, 10},
	(t_state_info){TK_GREATER, 11},
	(t_state_info){TK_LESS_LESS, 12},
	(t_state_info){TK_GREATER_GREATER, 13},
	(t_state_info){TK_PAREN_L, 7},
	(t_state_info){TK_NT_SIMPLE_COMMAND_ELEMENT, 6},
	(t_state_info){TK_NT_REDIRECTION, 9},
	(t_state_info){TK_NT_SIMPLE_COMMAND, 4},
	(t_state_info){TK_NT_COMMAND, 3},
	(t_state_info){TK_NT_SUBSHELL, 5},
	(t_state_info){TK_NT_LIST, 1},
	(t_state_info){TK_NT_PIPELINE, 2},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_1[] = {
	(t_state_info){TK_OR_OR, 14},
	(t_state_info){TK_AND_AND, 15},
	(t_state_info){TK_EOF, PARSER_ACCEPT},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_2[] = {
	(t_state_info){TK_PAREN_R, -15},
	(t_state_info){TK_OR_OR, -15},
	(t_state_info){TK_AND_AND, -15},
	(t_state_info){TK_OR, 16},
	(t_state_info){TK_EOF, -15},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_3[] = {
	(t_state_info){TK_PAREN_R, -18},
	(t_state_info){TK_OR_OR, -18},
	(t_state_info){TK_AND_AND, -18},
	(t_state_info){TK_OR, -18},
	(t_state_info){TK_EOF, -18},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_4[] = {
	(t_state_info){TK_WORD, 8},
	(t_state_info){TK_LESS, 10},
	(t_state_info){TK_GREATER, 11},
	(t_state_info){TK_LESS_LESS, 12},
	(t_state_info){TK_GREATER_GREATER, 13},
	(t_state_info){TK_PAREN_R, -11},
	(t_state_info){TK_OR_OR, -11},
	(t_state_info){TK_AND_AND, -11},
	(t_state_info){TK_OR, -11},
	(t_state_info){TK_EOF, -11},
	(t_state_info){TK_NT_SIMPLE_COMMAND_ELEMENT, 17},
	(t_state_info){TK_NT_REDIRECTION, 9},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_5[] = {
	(t_state_info){TK_LESS, 10},
	(t_state_info){TK_GREATER, 11},
	(t_state_info){TK_LESS_LESS, 12},
	(t_state_info){TK_GREATER_GREATER, 13},
	(t_state_info){TK_PAREN_R, -12},
	(t_state_info){TK_OR_OR, -12},
	(t_state_info){TK_AND_AND, -12},
	(t_state_info){TK_OR, -12},
	(t_state_info){TK_EOF, -12},
	(t_state_info){TK_NT_SIMPLE_COMMAND, 19},
	(t_state_info){TK_NT_REDIRECTION_LIST, 18},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_6[] = {
	(t_state_info){TK_WORD, -7},
	(t_state_info){TK_LESS, -7},
	(t_state_info){TK_GREATER, -7},
	(t_state_info){TK_LESS_LESS, -7},
	(t_state_info){TK_GREATER_GREATER, -7},
	(t_state_info){TK_PAREN_R, -7},
	(t_state_info){TK_OR_OR, -7},
	(t_state_info){TK_AND_AND, -7},
	(t_state_info){TK_OR, -7},
	(t_state_info){TK_EOF, -7},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_7[] = {
	(t_state_info){TK_WORD, 8},
	(t_state_info){TK_LESS, 10},
	(t_state_info){TK_GREATER, 11},
	(t_state_info){TK_LESS_LESS, 12},
	(t_state_info){TK_GREATER_GREATER, 13},
	(t_state_info){TK_PAREN_L, 7},
	(t_state_info){TK_NT_SIMPLE_COMMAND_ELEMENT, 6},
	(t_state_info){TK_NT_REDIRECTION, 9},
	(t_state_info){TK_NT_SIMPLE_COMMAND, 4},
	(t_state_info){TK_NT_COMMAND, 3},
	(t_state_info){TK_NT_SUBSHELL, 5},
	(t_state_info){TK_NT_LIST, 20},
	(t_state_info){TK_NT_PIPELINE, 2},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_8[] = {
	(t_state_info){TK_WORD, -1},
	(t_state_info){TK_LESS, -1},
	(t_state_info){TK_GREATER, -1},
	(t_state_info){TK_LESS_LESS, -1},
	(t_state_info){TK_GREATER_GREATER, -1},
	(t_state_info){TK_PAREN_R, -1},
	(t_state_info){TK_OR_OR, -1},
	(t_state_info){TK_AND_AND, -1},
	(t_state_info){TK_OR, -1},
	(t_state_info){TK_EOF, -1},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_9[] = {
	(t_state_info){TK_WORD, -2},
	(t_state_info){TK_LESS, -2},
	(t_state_info){TK_GREATER, -2},
	(t_state_info){TK_LESS_LESS, -2},
	(t_state_info){TK_GREATER_GREATER, -2},
	(t_state_info){TK_PAREN_R, -2},
	(t_state_info){TK_OR_OR, -2},
	(t_state_info){TK_AND_AND, -2},
	(t_state_info){TK_OR, -2},
	(t_state_info){TK_EOF, -2},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_10[] = {
	(t_state_info){TK_WORD, 21},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_11[] = {
	(t_state_info){TK_WORD, 22},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_12[] = {
	(t_state_info){TK_WORD, 23},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_13[] = {
	(t_state_info){TK_WORD, 24},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_14[] = {
	(t_state_info){TK_WORD, 8},
	(t_state_info){TK_LESS, 10},
	(t_state_info){TK_GREATER, 11},
	(t_state_info){TK_LESS_LESS, 12},
	(t_state_info){TK_GREATER_GREATER, 13},
	(t_state_info){TK_PAREN_L, 7},
	(t_state_info){TK_NT_SIMPLE_COMMAND_ELEMENT, 6},
	(t_state_info){TK_NT_REDIRECTION, 9},
	(t_state_info){TK_NT_SIMPLE_COMMAND, 4},
	(t_state_info){TK_NT_COMMAND, 3},
	(t_state_info){TK_NT_SUBSHELL, 5},
	(t_state_info){TK_NT_PIPELINE, 25},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_15[] = {
	(t_state_info){TK_WORD, 8},
	(t_state_info){TK_LESS, 10},
	(t_state_info){TK_GREATER, 11},
	(t_state_info){TK_LESS_LESS, 12},
	(t_state_info){TK_GREATER_GREATER, 13},
	(t_state_info){TK_PAREN_L, 7},
	(t_state_info){TK_NT_SIMPLE_COMMAND_ELEMENT, 6},
	(t_state_info){TK_NT_REDIRECTION, 9},
	(t_state_info){TK_NT_SIMPLE_COMMAND, 4},
	(t_state_info){TK_NT_COMMAND, 3},
	(t_state_info){TK_NT_SUBSHELL, 5},
	(t_state_info){TK_NT_PIPELINE, 26},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_16[] = {
	(t_state_info){TK_WORD, 8},
	(t_state_info){TK_LESS, 10},
	(t_state_info){TK_GREATER, 11},
	(t_state_info){TK_LESS_LESS, 12},
	(t_state_info){TK_GREATER_GREATER, 13},
	(t_state_info){TK_PAREN_L, 7},
	(t_state_info){TK_NT_SIMPLE_COMMAND_ELEMENT, 6},
	(t_state_info){TK_NT_REDIRECTION, 9},
	(t_state_info){TK_NT_SIMPLE_COMMAND, 4},
	(t_state_info){TK_NT_COMMAND, 27},
	(t_state_info){TK_NT_SUBSHELL, 5},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_17[] = {
	(t_state_info){TK_WORD, -8},
	(t_state_info){TK_LESS, -8},
	(t_state_info){TK_GREATER, -8},
	(t_state_info){TK_LESS_LESS, -8},
	(t_state_info){TK_GREATER_GREATER, -8},
	(t_state_info){TK_PAREN_R, -8},
	(t_state_info){TK_OR_OR, -8},
	(t_state_info){TK_AND_AND, -8},
	(t_state_info){TK_OR, -8},
	(t_state_info){TK_EOF, -8},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_18[] = {
	(t_state_info){TK_LESS, 10},
	(t_state_info){TK_GREATER, 11},
	(t_state_info){TK_LESS_LESS, 12},
	(t_state_info){TK_GREATER_GREATER, 13},
	(t_state_info){TK_PAREN_R, -13},
	(t_state_info){TK_OR_OR, -13},
	(t_state_info){TK_AND_AND, -13},
	(t_state_info){TK_OR, -13},
	(t_state_info){TK_EOF, -13},
	(t_state_info){TK_NT_REDIRECTION, 28},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_19[] = {
	(t_state_info){TK_LESS, -9},
	(t_state_info){TK_GREATER, -9},
	(t_state_info){TK_LESS_LESS, -9},
	(t_state_info){TK_GREATER_GREATER, -9},
	(t_state_info){TK_PAREN_R, -9},
	(t_state_info){TK_OR_OR, -9},
	(t_state_info){TK_AND_AND, -9},
	(t_state_info){TK_OR, -9},
	(t_state_info){TK_EOF, -9},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_20[] = {
	(t_state_info){TK_PAREN_R, 29},
	(t_state_info){TK_OR_OR, 14},
	(t_state_info){TK_AND_AND, 15},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_21[] = {
	(t_state_info){TK_WORD, -3},
	(t_state_info){TK_LESS, -3},
	(t_state_info){TK_GREATER, -3},
	(t_state_info){TK_LESS_LESS, -3},
	(t_state_info){TK_GREATER_GREATER, -3},
	(t_state_info){TK_PAREN_R, -3},
	(t_state_info){TK_OR_OR, -3},
	(t_state_info){TK_AND_AND, -3},
	(t_state_info){TK_OR, -3},
	(t_state_info){TK_EOF, -3},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_22[] = {
	(t_state_info){TK_WORD, -4},
	(t_state_info){TK_LESS, -4},
	(t_state_info){TK_GREATER, -4},
	(t_state_info){TK_LESS_LESS, -4},
	(t_state_info){TK_GREATER_GREATER, -4},
	(t_state_info){TK_PAREN_R, -4},
	(t_state_info){TK_OR_OR, -4},
	(t_state_info){TK_AND_AND, -4},
	(t_state_info){TK_OR, -4},
	(t_state_info){TK_EOF, -4},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_23[] = {
	(t_state_info){TK_WORD, -5},
	(t_state_info){TK_LESS, -5},
	(t_state_info){TK_GREATER, -5},
	(t_state_info){TK_LESS_LESS, -5},
	(t_state_info){TK_GREATER_GREATER, -5},
	(t_state_info){TK_PAREN_R, -5},
	(t_state_info){TK_OR_OR, -5},
	(t_state_info){TK_AND_AND, -5},
	(t_state_info){TK_OR, -5},
	(t_state_info){TK_EOF, -5},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_24[] = {
	(t_state_info){TK_WORD, -6},
	(t_state_info){TK_LESS, -6},
	(t_state_info){TK_GREATER, -6},
	(t_state_info){TK_LESS_LESS, -6},
	(t_state_info){TK_GREATER_GREATER, -6},
	(t_state_info){TK_PAREN_R, -6},
	(t_state_info){TK_OR_OR, -6},
	(t_state_info){TK_AND_AND, -6},
	(t_state_info){TK_OR, -6},
	(t_state_info){TK_EOF, -6},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_25[] = {
	(t_state_info){TK_PAREN_R, -16},
	(t_state_info){TK_OR_OR, -16},
	(t_state_info){TK_AND_AND, -16},
	(t_state_info){TK_OR, 16},
	(t_state_info){TK_EOF, -16},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_26[] = {
	(t_state_info){TK_PAREN_R, -17},
	(t_state_info){TK_OR_OR, -17},
	(t_state_info){TK_AND_AND, -17},
	(t_state_info){TK_OR, 16},
	(t_state_info){TK_EOF, -17},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_27[] = {
	(t_state_info){TK_PAREN_R, -19},
	(t_state_info){TK_OR_OR, -19},
	(t_state_info){TK_AND_AND, -19},
	(t_state_info){TK_OR, -19},
	(t_state_info){TK_EOF, -19},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_28[] = {
	(t_state_info){TK_LESS, -10},
	(t_state_info){TK_GREATER, -10},
	(t_state_info){TK_LESS_LESS, -10},
	(t_state_info){TK_GREATER_GREATER, -10},
	(t_state_info){TK_PAREN_R, -10},
	(t_state_info){TK_OR_OR, -10},
	(t_state_info){TK_AND_AND, -10},
	(t_state_info){TK_OR, -10},
	(t_state_info){TK_EOF, -10},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_29[] = {
	(t_state_info){TK_LESS, -14},
	(t_state_info){TK_GREATER, -14},
	(t_state_info){TK_LESS_LESS, -14},
	(t_state_info){TK_GREATER_GREATER, -14},
	(t_state_info){TK_PAREN_R, -14},
	(t_state_info){TK_OR_OR, -14},
	(t_state_info){TK_AND_AND, -14},
	(t_state_info){TK_OR, -14},
	(t_state_info){TK_EOF, -14},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info *const	g_parser_state_table[] = {
	g_parser_state_0,
	g_parser_state_1,
	g_parser_state_2,
	g_parser_state_3,
	g_parser_state_4,
	g_parser_state_5,
	g_parser_state_6,
	g_parser_state_7,
	g_parser_state_8,
	g_parser_state_9,
	g_parser_state_10,
	g_parser_state_11,
	g_parser_state_12,
	g_parser_state_13,
	g_parser_state_14,
	g_parser_state_15,
	g_parser_state_16,
	g_parser_state_17,
	g_parser_state_18,
	g_parser_state_19,
	g_parser_state_20,
	g_parser_state_21,
	g_parser_state_22,
	g_parser_state_23,
	g_parser_state_24,
	g_parser_state_25,
	g_parser_state_26,
	g_parser_state_27,
	g_parser_state_28,
	g_parser_state_29,
};

t_parser_state	parser_state(t_parser_state state, t_token_kind token)
{
	const t_state_info	*info = g_parser_state_table[state];
	size_t				i;

	i = 0;
	while (info[i].token != TK_ERROR)
	{
		if (info[i].token == token)
			return (info[i].state);
		i++;
	}
	return (PARSER_ERROR);
}
