/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:18:12 by jkong             #+#    #+#             */
/*   Updated: 2022/06/15 19:22:23 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_mem.h"
#include "generic_list.h"

void	set_redirect(t_redirect *item, int src, t_redirection r, t_word *dest)
{
	item->redirectee = src;
	item->instruction = r;
	item->word = *dest;
}

void	dispose_redirect(t_redirect *item)
{
	dispose_word(&item->word);
}

t_list_redirect	*append_redirect(t_list_redirect **list, t_redirect *item)
{
	t_list_redirect	*elem;

	elem = calloc_safe(1, sizeof(t_list_redirect));
	elem->redirect = *item;
	list_append((void *)list, (void *)elem);
	return (elem);
}

void	subshell_apply_redirect(t_subshell_command *subshell,
	t_list_redirect *r_list)
{
	subshell->redirect_list = r_list;
}
