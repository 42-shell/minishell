/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_fuse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:35:56 by jkong             #+#    #+#             */
/*   Updated: 2022/06/23 19:04:54 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "util_flag.h"
#include "string_buffer.h"
#include "string_vector.h"

static t_str_buf	*_str_append_param(t_str_buf *buf, char *str, size_t *len,
	t_list_var *v_list)
{
	char	*name;

	if (legal_variable_starter(str[*len]))
	{
		(*len)++;
		while (legal_variable_char(str[*len]))
			(*len)++;
	}
	else if (str[*len] == '?')
		(*len)++;
	if (*len - 1)
	{
		name = str_dispose(str_append_raw(NULL, str + 1, *len - 1));
		if (ft_strcmp(name, "?") == 0)
			buf = str_append_number(buf, g_exit_status);
		else
			buf = str_append(buf, get_var(v_list, name, 0));
		free(name);
	}
	else
		buf = str_append_raw(buf, str, 1);
	return (buf);
}

static t_str_buf	*_str_append_param_expand(t_str_buf *buf, char *str,
	t_list_var *v_list)
{
	size_t	len;

	while (*str)
	{
		len = 0;
		while (str[len] && !has_flag(get_char_flags(str[len]), CF_EXPANSION))
			len++;
		if (len)
			buf = str_append_raw(buf, str, len);
		str += len;
		if (*str)
		{
			len = 1;
			buf = _str_append_param(buf, str, &len, v_list);
			str += len;
		}
	}
	return (buf);
}

static char	*_subst(char *str, char from, char to)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == from)
			str[i] = to;
		i++;
	}
	return (str);
}

char	*join_expand_word_list(t_list_word *w_list, t_list_var *v_list,
	int glob)
{
	const int	expand_param = !!v_list;
	t_list_word	*it;
	t_str_buf	*buf;
	t_str_buf	*buf_temp;
	char		*str;

	it = w_list;
	buf = NULL;
	while (it)
	{
		str = it->word.str;
		if (expand_param && has_flag(it->word.flags, WF_HAS_DOLLAR))
			buf_temp = _str_append_param_expand(NULL, str, v_list);
		else
			buf_temp = str_append(NULL, str);
		str = str_dispose(buf_temp);
		if (glob && has_flag(it->word.flags, WF_GLOB))
			str = _subst(str, '*', '\001');
		buf = str_append(buf, str);
		free(str);
		it = it->next;
	}
	return (str_dispose(buf));
}

t_str_vec	*file_expand(t_str_vec *vec, char *path, char *str)
{
	char **const	glob = glob_to_strvec(path, str);
	size_t			i;
	char			*str_temp;

	if (glob && *glob)
	{
		i = 0;
		while (glob[i])
		{
			str_temp = str_dispose(str_append(NULL, glob[i]));
			vec = strv_append(vec, str_temp);
			i++;
		}
	}
	else
	{
		str_temp = str_dispose(str_append(NULL, str));
		str_temp = _subst(str_temp, '\001', '*');
		vec = strv_append(vec, str_temp);
	}
	free_strvec(glob);
	return (vec);
}
