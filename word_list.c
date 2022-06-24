/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:35:56 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 19:32:27 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_mem.h"
#include "string_buffer.h"
#include "generic_list.h"

void	append_word_list(t_list_word **list_ptr, char *str, t_word_flags flags)
{
	t_list_word	*elem;

	elem = calloc_safe(1, sizeof(*elem));
	elem->word.str = str;
	elem->word.flags = flags;
	list_append((void *)list_ptr, (void *)elem);
}

static int	_clear_w_list(t_list_word *elem)
{
	dispose_word(&elem->word);
	free(elem);
	return (0);
}

void	delete_word_list(t_list_word *list)
{
	list_walk((void *)list, _clear_w_list);
}

void	singleton_word_list(t_list_word *ptr, t_word *word)
{
	ptr->word.str = word->str;
	ptr->word.flags = word->flags;
	ptr->next = NULL;
}
