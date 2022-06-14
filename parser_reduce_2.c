/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reduce_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/06/14 13:56:03 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//redirection_list -> redirection_list redirection
t_token_kind	parser_reduce_10(t_parser *pst)
{
	t_parser_stack	val;
	t_command		command_lhs;
	t_command		command_rhs;

	ft_memset(&val, 0, sizeof(val));
	ft_memset(&command_lhs, 0, sizeof(command_lhs));
	swap_command(&command_lhs, &pst->now[-1].command);
	ft_memset(&command_rhs, 0, sizeof(command_rhs));
	swap_command(&command_rhs, &pst->now[0].command);
	combine_simple_command(command_lhs.value.simple, command_rhs.value.simple);
	val.command = command_lhs;
	dispose_command(&command_rhs);
	clear_parser_stack_item(&pst->now[-1]);
	clear_parser_stack_item(&pst->now[0]);
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
	t_parser_stack	val;
	t_command		command_lhs;
	t_command		command_rhs;

	ft_memset(&val, 0, sizeof(val));
	ft_memset(&command_lhs, 0, sizeof(command_lhs));
	swap_command(&command_lhs, &pst->now[-1].command);
	ft_memset(&command_rhs, 0, sizeof(command_rhs));
	swap_command(&command_rhs, &pst->now[0].command);
	subshell_apply_redirect(command_lhs.value.subshell,
		command_rhs.value.simple->redirect_list);
	command_rhs.value.simple->redirect_list = NULL;
	val.command = command_lhs;
	dispose_command(&command_rhs);
	clear_parser_stack_item(&pst->now[-1]);
	clear_parser_stack_item(&pst->now[0]);
	pst->now -= 2;
	*++pst->now = val;
	return (TK_NT_COMMAND);
}

//subshell -> '(' list ')'
t_token_kind	parser_reduce_14(t_parser *pst)
{
	t_parser_stack	val;
	t_command		command;

	ft_memset(&val, 0, sizeof(val));
	ft_memset(&command, 0, sizeof(command));
	swap_command(&command, &pst->now[0].command);
	val.command.type = CMD_SUBSHELL;
	val.command.value.subshell = make_subshell(&command);
	clear_parser_stack_item(&pst->now[-2]);
	clear_parser_stack_item(&pst->now[-1]);
	clear_parser_stack_item(&pst->now[0]);
	pst->now -= 3;
	*++pst->now = val;
	return (TK_NT_SUBSHELL);
}
