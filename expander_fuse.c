/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_fuse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:35:56 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 20:16:47 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "util_flag.h"
#include "string_buffer.h"
#include "string_vector.h"

static char	*_subst(char *str, char from, char to)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == from)
			str[i] = to;
		i++;
	}
	return (str);
}

static t_str_vec	*_expand_file_glob(t_str_vec *vec, char *path, char *s)
{
	char **const	glob = glob_to_strvec(path, s);
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
		str_temp = str_dispose(str_append(NULL, s));
		str_temp = _subst(str_temp, '\001', '*');
		vec = strv_append(vec, str_temp);
	}
	free_strvec(glob);
	return (vec);
}

char	**expand_collect(t_list_word *w_list, char *path)
{
	t_list_word	*it;
	t_str_vec	*vec;
	t_str_buf	*buf;
	char		*str;

	vec = NULL;
	buf = NULL;
	it = w_list;
	while (it)
	{
		str = str_dispose(str_append(NULL, it->word.str));
		if (has_flag(it->word.flags, WF_SPLITSPACE))
			str = _subst(str, '*', '\001');
		buf = str_append(buf, str);
		free(str);
		if ((buf && has_flag(it->word.flags, WF_IFS)) || !it->next)
		{
			str = str_dispose(buf);
			vec = _expand_file_glob(vec, path, str);
			free(str);
			buf = NULL;
		}
		it = it->next;
	}
	return (strv_dispose(vec));
}

char	*expand_collect_standalone(t_list_word *w_list)
{
	t_list_word	*it;
	t_str_buf	*buf;
	char		*str;

	it = w_list;
	buf = NULL;
	while (it)
	{
		str = str_dispose(str_append(NULL, it->word.str));
		buf = str_append(buf, str);
		free(str);
		it = it->next;
	}
	return (str_dispose(buf));
}
