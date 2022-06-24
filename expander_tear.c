/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:35:56 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 20:13:10 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_flag.h"
#include "libft.h"
#include "string_buffer.h"
#include "generic_list.h"

static void	_append_quote(t_list_word **new_list_ptr, t_list_word *item,
	t_list_var *v_list)
{
	char	*str;
	size_t	len;
	char	*value;
	int		flags;

	(void)v_list;
	str = item->word.str;
	while (*str != '\0')
	{
		len = next_syntax(str, CFV_QUOTE);
		value = str_dispose(str_append_raw(NULL, str, len));
		append_word_list(new_list_ptr, value, WFV_NOQUOTE);
		str += len;
		if (*str != '\0')
		{
			len = 1;
			while (str[len] != '\0' && str[len] != *str)
				len++;
			value = str_dispose(str_append_raw(NULL, str + 1, len - 1));
			flags = (*str == '\"') * WFV_DBLQUOTE;
			append_word_list(new_list_ptr, value, flags);
			str += len + 1;
		}
	}
}

static char	*_get_param_value(char *buf, size_t *len, t_list_var *v_list)
{
	char		*name;
	t_str_buf	*value;

	*len = 1;
	if (legal_variable_starter(buf[*len]))
	{
		(*len)++;
		while (legal_variable_char(buf[*len]))
			(*len)++;
	}
	else if (ft_strchr("?", buf[*len]))
		(*len)++;
	if (*len - 1)
	{
		name = str_dispose(str_append_raw(NULL, buf + 1, *len - 1));
		if (ft_strcmp(name, "?") == 0)
			value = str_append_number(NULL, g_exit_status);
		else
			value = str_append(NULL, get_var(v_list, name, 0));
		free(name);
	}
	else
		value = str_append_raw(NULL, buf, 1);
	return (str_dispose(value));
}

static void	_append_param(t_list_word **new_list_ptr, t_list_word *item,
	t_list_var *v_list)
{
	char			*str;
	char			*value;
	size_t			len;
	int				flags;

	str = item->word.str;
	flags = item->word.flags;
	while (*str != '\0' && has_flag(flags, WF_HAS_DOLLAR))
	{
		len = next_syntax(str, CFV_EXPANSION);
		value = str_dispose(str_append_raw(NULL, str, len));
		append_word_list(new_list_ptr, value, flags);
		str += len;
		if (*str != '\0')
		{
			value = _get_param_value(str, &len, v_list);
			append_word_list(new_list_ptr, value, add_flag(flags, WF_PARAM));
			str += len;
		}
	}
	value = str_dispose(str_append(NULL, str));
	append_word_list(new_list_ptr, value, flags);
}

static void	_append_split(t_list_word **new_list_ptr, t_list_word *item,
	t_list_var *v_list)
{
	char			*str;
	char			*value;
	size_t			len;
	int				flags;

	str = item->word.str;
	flags = item->word.flags;
	while (*str != '\0' && has_flag(flags, WF_SPLITSPACE)
		&& has_flag(flags, WF_PARAM))
	{
		len = 0;
		while (str[len] != '\0' && ft_strchr(get_ifs(v_list), str[len]))
			len++;
		str += len;
		if (len != 0)
			append_word_list(new_list_ptr, str_dispose(NULL), WFV_IFS);
		len = 0;
		while (str[len] != '\0' && !ft_strchr(get_ifs(v_list), str[len]))
			len++;
		value = str_dispose(str_append_raw(NULL, str, len));
		append_word_list(new_list_ptr, value, flags);
		str += len;
	}
	value = str_dispose(str_append(NULL, str));
	append_word_list(new_list_ptr, value, flags);
}

t_list_word	*expand_map(t_list_word *w_list, t_list_var *v_list, int mode)
{
	t_list_word	*new_list;

	new_list = NULL;
	while (w_list)
	{
		if (mode == 1)
			_append_quote(&new_list, w_list, v_list);
		else if (mode == 2)
			_append_param(&new_list, w_list, v_list);
		else if (mode == 3)
			_append_split(&new_list, w_list, v_list);
		w_list = w_list->next;
	}
	return (new_list);
}
