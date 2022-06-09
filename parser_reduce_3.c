/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reduce_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/06/09 22:06:54 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//list -> pipeline
t_token_kind	parser_reduce_15(t_parser *pst)
{
	(void)&pst;
	return (TK_NT_LIST);
}

//list -> list '||' pipeline
t_token_kind	parser_reduce_16(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//connect_command
	pst->now -= 3;
	*++pst->now = val;
	return (TK_NT_LIST);
}

//list -> list '&&' pipeline
t_token_kind	parser_reduce_17(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//connect_command
	pst->now -= 3;
	*++pst->now = val;
	return (TK_NT_LIST);
}

//pipeline -> command
t_token_kind	parser_reduce_18(t_parser *pst)
{
	(void)&pst;
	return (TK_NT_PIPELINE);
}

//pipeline -> pipeline '|' command
t_token_kind	parser_reduce_19(t_parser *pst)
{
	t_parse_stack	val;

	val = *pst->now;
	//connect_command
	pst->now -= 3;
	*++pst->now = val;
	return (TK_NT_PIPELINE);
}
