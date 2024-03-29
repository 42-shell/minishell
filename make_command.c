/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:10:34 by jkong             #+#    #+#             */
/*   Updated: 2022/06/19 00:34:08 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_mem.h"
#include "generic_list.h"

t_simple_command	*make_simple_command(void)
{
	t_simple_command	*cmd;

	cmd = malloc_safe(sizeof(*cmd));
	cmd->flags = 0;
	cmd->word_list = NULL;
	cmd->redirect_list = NULL;
	return (cmd);
}

t_subshell_command	*make_subshell(t_command *container)
{
	t_subshell_command	*cmd;

	cmd = malloc_safe(sizeof(*cmd));
	cmd->flags = 0;
	cmd->container = *container;
	cmd->redirect_list = NULL;
	return (cmd);
}

t_command_connection	*connect_command(t_command *lhs, t_command *rhs,
	t_token_kind connector)
{
	t_command_connection	*cmd;

	cmd = malloc_safe(sizeof(*cmd));
	cmd->flags = 0;
	cmd->connector = connector;
	cmd->first = *lhs;
	cmd->second = *rhs;
	return (cmd);
}

void	append_word(t_list_word **list, t_word *item)
{
	t_list_word	*elem;

	elem = calloc_safe(1, sizeof(t_list_word));
	elem->word = *item;
	list_append((void *)list, (void *)elem);
}

void	combine_simple_command(t_simple_command *lhs, t_simple_command *rhs)
{
	lhs->flags |= rhs->flags;
	rhs->flags = 0;
	list_append((void *)&lhs->word_list, (void *)rhs->word_list);
	rhs->word_list = NULL;
	list_append((void *)&lhs->redirect_list, (void *)rhs->redirect_list);
	rhs->redirect_list = NULL;
}
