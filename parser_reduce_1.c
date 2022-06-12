/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reduce_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/06/09 21:36:00 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//redirection -> '<<' WORD
t_token_kind	parser_reduce_5(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//make_redirect
	pst->now -= 2;
	*++pst->now = val;
	//push_heredoc
	return (TK_NT_REDIRECTION);
}

//redirection -> '>>' WORD
t_token_kind	parser_reduce_6(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//make_redirect
	pst->now -= 2;
	*++pst->now = val;
	return (TK_NT_REDIRECTION);
}

//simple_command -> simple_command_element
t_token_kind	parser_reduce_7(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//make_command
	pst->now -= 1;
	*++pst->now = val;
	return (TK_NT_SIMPLE_COMMAND);
}

//simple_command -> simple_command simple_command_element
t_token_kind	parser_reduce_8(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//make_command
	pst->now -= 2;
	*++pst->now = val;
	return (TK_NT_SIMPLE_COMMAND);
}

//redirection_list -> redirection
t_token_kind	parser_reduce_9(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//append_redirect
	pst->now -= 1;
	*++pst->now = val;
	return (TK_NT_REDIRECTION_LIST);
}
