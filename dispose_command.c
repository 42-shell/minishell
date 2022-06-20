/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:10:34 by jkong             #+#    #+#             */
/*   Updated: 2022/06/20 21:55:52 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "generic_list.h"

void	dispose_word(t_word *item)
{
	free(item->str);
	item->str = NULL;
}

void	dispose_redirect(t_redirect *item)
{
	dispose_word(&item->word);
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

void	dispose_command(t_command *item)
{
	if (item->type == CMD_SIMPLE)
	{
		list_walk((void *)item->value.simple->word_list, _clear_w_list);
		list_walk((void *)item->value.simple->redirect_list, _clear_r_list);
	}
	else if (item->type == CMD_SUBSHELL)
	{
		dispose_command(&item->value.subshell->container);
		list_walk((void *)item->value.subshell->redirect_list, _clear_r_list);
	}
	else if (item->type == CMD_CONNECTION)
	{
		dispose_command(&item->value.connection->first);
		dispose_command(&item->value.connection->second);
	}
	free(item->value.ptr);
	item->value.ptr = NULL;
}
