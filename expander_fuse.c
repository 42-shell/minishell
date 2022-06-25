/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_fuse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:35:56 by jkong             #+#    #+#             */
/*   Updated: 2022/06/26 01:33:46 by jkong            ###   ########.fr       */
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
		sort_strvec(glob, ft_strcmp);
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
	t_str_vec	*vec;
	t_str_buf	*buf;
	char		*str;

	vec = NULL;
	buf = NULL;
	while (w_list)
	{
		str = str_dispose(str_append(NULL, w_list->word.str));
		if (has_flag(w_list->word.flags, WF_SPLIT))
			str = _subst(str, '*', '\001');
		if (!has_flag(w_list->word.flags, WF_IFS))
			buf = str_append(buf, str);
		free(str);
		if (buf && (has_flag(w_list->word.flags, WF_IFS) || !w_list->next))
		{
			str = str_dispose(buf);
			vec = _expand_file_glob(vec, path, str);
			free(str);
			buf = NULL;
		}
		w_list = w_list->next;
	}
	return (strv_dispose(vec));
}

char	*expand_collect_standalone(t_list_word *w_list)
{
	t_str_buf	*buf;
	char		*str;

	buf = NULL;
	while (w_list)
	{
		str = str_dispose(str_append(NULL, w_list->word.str));
		buf = str_append(buf, str);
		free(str);
		w_list = w_list->next;
	}
	return (str_dispose(buf));
}
