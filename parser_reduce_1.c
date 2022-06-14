/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reduce_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/06/14 16:56:19 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

//redirection -> '<<' WORD
t_token_kind	parser_reduce_5(t_parser *pst)
{
	t_parser_stack	val;
	t_word			word;

	ft_memset(&val, 0, sizeof(val));
	ft_memset(&word, 0, sizeof(word));
	swap_word(&word, &pst->now[0].word);
	set_redirect(&val.redirect, STDIN_FILENO, R_READING_UNTIL, &word);
	clear_parser_stack_item(&pst->now[-1]);
	clear_parser_stack_item(&pst->now[0]);
	pst->now -= 2;
	*++pst->now = val;
	//push_heredoc
	return (TK_NT_REDIRECTION);
}

//redirection -> '>>' WORD
t_token_kind	parser_reduce_6(t_parser *pst)
{
	t_parser_stack	val;
	t_word			word;

	ft_memset(&val, 0, sizeof(val));
	ft_memset(&word, 0, sizeof(word));
	swap_word(&word, &pst->now[0].word);
	set_redirect(&val.redirect, STDOUT_FILENO, R_APPENDING_TO, &word);
	clear_parser_stack_item(&pst->now[-1]);
	clear_parser_stack_item(&pst->now[0]);
	pst->now -= 2;
	*++pst->now = val;
	return (TK_NT_REDIRECTION);
}

//simple_command -> simple_command_element
t_token_kind	parser_reduce_7(t_parser *pst)
{
	(void)&pst;
	return (TK_NT_SIMPLE_COMMAND);
}

//simple_command -> simple_command simple_command_element
t_token_kind	parser_reduce_8(t_parser *pst)
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
	return (TK_NT_SIMPLE_COMMAND);
}

//redirection_list -> redirection
t_token_kind	parser_reduce_9(t_parser *pst)
{
	t_parser_stack	val;
	t_redirect		redirect;

	ft_memset(&val, 0, sizeof(val));
	val.command.type = CMD_SIMPLE;
	val.command.value.simple = make_simple_command();
	ft_memset(&redirect, 0, sizeof(redirect));
	swap_redirect(&redirect, &val.redirect);
	append_redirect(&val.command.value.simple->redirect_list, &redirect);
	clear_parser_stack_item(&pst->now[0]);
	pst->now -= 1;
	*++pst->now = val;
	return (TK_NT_REDIRECTION_LIST);
}
