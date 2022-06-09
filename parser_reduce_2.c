/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reduce_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/06/09 21:39:53 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//redirection_list -> redirection_list redirection
t_token_kind	parser_reduce_10(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//append_list
	pst->now -= 2;
	*++pst->now = val;
	return (TK_NT_REDIRECTION_LIST);
}

//command -> simple_command
t_token_kind	parser_reduce_11(t_parser *pst)
{
	(void)&pst;
	return (TK_NT_COMMAND);
}

//command -> subshell
t_token_kind	parser_reduce_12(t_parser *pst)
{
	(void)&pst;
	return (TK_NT_COMMAND);
}

//command -> subshell redirection_list
t_token_kind	parser_reduce_13(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//subshell_put_option
	pst->now -= 2;
	*++pst->now = val;
	return (TK_NT_COMMAND);
}

//subshell -> '(' list ')'
t_token_kind	parser_reduce_14(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//make_command
	pst->now -= 3;
	*++pst->now = val;
	return (TK_NT_SUBSHELL);
}
