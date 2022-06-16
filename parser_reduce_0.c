/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reduce_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/06/16 18:31:52 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

//S -> list
t_token_kind	parser_reduce_0(t_parser *pst)
{
	(void)&pst;
	return (TK_NT_ACCEPT);
}

//simple_command_element -> WORD
t_token_kind	parser_reduce_1(t_parser *pst)
{
	t_parser_stack	val;
	t_word			word;

	ft_memset(&val, 0, sizeof(val));
	val.command.type = CMD_SIMPLE;
	val.command.value.simple = make_simple_command();
	ft_memset(&word, 0, sizeof(word));
	swap_word(&word, &pst->now[0].word);
	append_word(&val.command.value.simple->word_list, &word);
	clear_parser_stack_item(&pst->now[0]);
	pst->now -= 1;
	*++pst->now = val;
	return (TK_NT_SIMPLE_COMMAND_ELEMENT);
}

//simple_command_element -> redirection
t_token_kind	parser_reduce_2(t_parser *pst)
{
	t_parser_stack	val;
	t_redirect		redirect;
	t_list_redirect	*r;

	ft_memset(&val, 0, sizeof(val));
	ft_memset(&redirect, 0, sizeof(redirect));
	swap_redirect(&redirect, &pst->now[0].redirect);
	val.command.type = CMD_SIMPLE;
	val.command.value.simple = make_simple_command();
	r = append_redirect(&val.command.value.simple->redirect_list, &redirect);
	if (redirect.instruction == R_READING_UNTIL)
		push_here_document(pst, r);
	clear_parser_stack_item(&pst->now[0]);
	pst->now -= 1;
	*++pst->now = val;
	return (TK_NT_SIMPLE_COMMAND_ELEMENT);
}

//redirection -> '<' WORD
t_token_kind	parser_reduce_3(t_parser *pst)
{
	t_parser_stack	val;
	t_word			word;

	ft_memset(&val, 0, sizeof(val));
	ft_memset(&word, 0, sizeof(word));
	swap_word(&word, &pst->now[0].word);
	set_redirect(&val.redirect, STDIN_FILENO, R_INPUT_DIRECTION, &word);
	clear_parser_stack_item(&pst->now[-1]);
	clear_parser_stack_item(&pst->now[0]);
	pst->now -= 2;
	*++pst->now = val;
	return (TK_NT_REDIRECTION);
}

//redirection -> '>' WORD
t_token_kind	parser_reduce_4(t_parser *pst)
{
	t_parser_stack	val;
	t_word			word;

	ft_memset(&val, 0, sizeof(val));
	ft_memset(&word, 0, sizeof(word));
	swap_word(&word, &pst->now[0].word);
	set_redirect(&val.redirect, STDOUT_FILENO, R_OUTPUT_DIRECTION, &word);
	clear_parser_stack_item(&pst->now[-1]);
	clear_parser_stack_item(&pst->now[0]);
	pst->now -= 2;
	*++pst->now = val;
	return (TK_NT_REDIRECTION);
}
