/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:10:34 by jkong             #+#    #+#             */
/*   Updated: 2022/06/17 01:54:02 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "generic_list.h"

void	dispose_word(t_word *item)
{
	free(item->str);
	item->str = NULL;
}

static int	_clear_w_list(t_list_word *elem)
{
	dispose_word(&elem->word);
	free(elem);
	return (0);
}

static int	_clear_r_list(t_list_redirect *elem)
{
	dispose_redirect(&elem->redirect);
	free(elem);
	return (0);
}

void	dispose_command(t_command *root)
{
	if (root->type == CMD_SIMPLE)
	{
		list_walk((void *)root->value.simple->word_list, _clear_w_list);
		list_walk((void *)root->value.simple->redirect_list, _clear_r_list);
	}
	else if (root->type == CMD_SUBSHELL)
	{
		dispose_command(&root->value.subshell->container);
		list_walk((void *)root->value.subshell->redirect_list, _clear_r_list);
	}
	else if (root->type == CMD_CONNECTION)
	{
		dispose_command(&root->value.connection->first);
		dispose_command(&root->value.connection->second);
	}
	free(root->value.ptr);
	root->value.ptr = NULL;
}
