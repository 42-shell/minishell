/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reduce_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/06/09 21:35:41 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//S -> list
t_token_kind	parser_reduce_0(t_parser *pst)
{
	(void)&pst;
	return (TK_NT_ACCEPT);
}

//simple_command_element -> WORD
t_token_kind	parser_reduce_1(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//make_element
	pst->now -= 1;
	*++pst->now = val;
	return (TK_NT_SIMPLE_COMMAND_ELEMENT);
}

//simple_command_element -> redirection
t_token_kind	parser_reduce_2(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//make_element
	pst->now -= 1;
	*++pst->now = val;
	return (TK_NT_SIMPLE_COMMAND_ELEMENT);
}

//redirection -> '<' WORD
t_token_kind	parser_reduce_3(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//make_redirect
	pst->now -= 2;
	*++pst->now = val;
	return (TK_NT_REDIRECTION);
}

//redirection -> '>' WORD
t_token_kind	parser_reduce_4(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//make_redirect
	pst->now -= 2;
	*++pst->now = val;
	return (TK_NT_REDIRECTION);
}
