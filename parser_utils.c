/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/06/14 16:06:14 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	swap_word(t_word *a, t_word *b)
{
	t_word	x;

	x = *a;
	*a = *b;
	*b = x;
}

void	swap_redirect(t_redirect *a, t_redirect *b)
{
	t_redirect	x;

	x = *a;
	*a = *b;
	*b = x;
}

void	swap_command(t_command *a, t_command *b)
{
	t_command	x;

	x = *a;
	*a = *b;
	*b = x;
}

void	clear_parser_stack_item(t_parser_stack *item)
{
	t_word		temp_word;
	t_redirect	temp_redirect;
	t_command	temp_command;

	ft_memset(&temp_word, 0, sizeof(temp_word));
	ft_memset(&temp_redirect, 0, sizeof(temp_redirect));
	ft_memset(&temp_command, 0, sizeof(temp_command));
	swap_word(&temp_word, &item->word);
	swap_redirect(&temp_redirect, &item->redirect);
	swap_command(&temp_command, &item->command);
	dispose_word(&temp_word);
	dispose_redirect(&temp_redirect);
	dispose_command(&temp_command);
}
