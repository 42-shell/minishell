/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:35:56 by jkong             #+#    #+#             */
/*   Updated: 2022/06/23 20:17:03 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_mem.h"
#include "util_flag.h"
#include "string_buffer.h"
#include "generic_list.h"

static void	_append_word(t_list_word **list_ptr, char *str, size_t len,
	char quote)
{
	t_list_word	*elem;
	t_str_buf	*buf;

	elem = calloc_safe(1, sizeof(*elem));
	buf = str_append_raw(NULL, str, len);
	elem->word.str = str_dispose(buf);
	if (!quote || quote == '\"')
		set_flag(&elem->word.flags, WF_HAS_DOLLAR);
	if (!quote)
		set_flag(&elem->word.flags, WF_GLOB);
	list_append((void *)list_ptr, (void *)elem);
}

t_list_word	*new_expand_word_list(t_word *word)
{
	t_list_word	*w_list;
	char		*str;
	size_t		len;

	w_list = NULL;
	str = word->str;
	while (*str)
	{
		len = 0;
		while (str[len] && !has_flag(get_char_flags(str[len]), CF_QUOTE))
			len++;
		if (len)
			_append_word(&w_list, str, len, '\0');
		str += len;
		if (*str)
		{
			len = 1;
			while (str[len] && str[len] != *str)
				len++;
			if (len - 1)
				_append_word(&w_list, str + 1, len - 1, *str);
			str += len + 1;
		}
	}
	return (w_list);
}

static int	_clear_w_list(t_list_word *elem)
{
	dispose_word(&elem->word);
	free(elem);
	return (0);
}

void	delete_expand_word_list(t_list_word *list)
{
	list_walk((void *)list, _clear_w_list);
}
