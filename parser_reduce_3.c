/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reduce_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/06/14 17:00:51 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//list -> pipeline
t_token_kind	parser_reduce_15(t_parser *pst)
{
	(void)&pst;
	return (TK_NT_LIST);
}

//list -> list '||' pipeline
t_token_kind	parser_reduce_16(t_parser *pst)
{
	t_parser_stack	val;
	t_command		command_lhs;
	t_command		command_rhs;

	ft_memset(&val, 0, sizeof(val));
	ft_memset(&command_lhs, 0, sizeof(command_lhs));
	swap_command(&command_lhs, &pst->now[-2].command);
	ft_memset(&command_rhs, 0, sizeof(command_rhs));
	swap_command(&command_rhs, &pst->now[0].command);
	val.command.type = CMD_CONNECTION;
	val.command.value.connection = connect_command(&command_lhs, &command_rhs,
			TK_OR_OR);
	clear_parser_stack_item(&pst->now[-2]);
	clear_parser_stack_item(&pst->now[-1]);
	clear_parser_stack_item(&pst->now[0]);
	pst->now -= 3;
	*++pst->now = val;
	return (TK_NT_LIST);
}

//list -> list '&&' pipeline
t_token_kind	parser_reduce_17(t_parser *pst)
{
	t_parser_stack	val;
	t_command		command_lhs;
	t_command		command_rhs;

	ft_memset(&val, 0, sizeof(val));
	ft_memset(&command_lhs, 0, sizeof(command_lhs));
	swap_command(&command_lhs, &pst->now[-2].command);
	ft_memset(&command_rhs, 0, sizeof(command_rhs));
	swap_command(&command_rhs, &pst->now[0].command);
	val.command.type = CMD_CONNECTION;
	val.command.value.connection = connect_command(&command_lhs, &command_rhs,
			TK_AND_AND);
	clear_parser_stack_item(&pst->now[-2]);
	clear_parser_stack_item(&pst->now[-1]);
	clear_parser_stack_item(&pst->now[0]);
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
	t_parser_stack	val;
	t_command		command_lhs;
	t_command		command_rhs;

	ft_memset(&val, 0, sizeof(val));
	ft_memset(&command_lhs, 0, sizeof(command_lhs));
	swap_command(&command_lhs, &pst->now[-2].command);
	ft_memset(&command_rhs, 0, sizeof(command_rhs));
	swap_command(&command_rhs, &pst->now[0].command);
	val.command.type = CMD_CONNECTION;
	val.command.value.connection = connect_command(&command_lhs, &command_rhs,
			TK_OR);
	clear_parser_stack_item(&pst->now[-2]);
	clear_parser_stack_item(&pst->now[-1]);
	clear_parser_stack_item(&pst->now[0]);
	pst->now -= 3;
	*++pst->now = val;
	return (TK_NT_PIPELINE);
}
