/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:32:39 by jkong             #+#    #+#             */
/*   Updated: 2022/06/22 19:17:17 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_flag.h"
#include "safe_mem.h"
#include "libft.h"
#include "string_buffer.h"
#include "string_vector.h"

extern char	**environ;

static char	*_make_pair(const char *s, char **val_ptr, char delim)
{
	const size_t	len = ft_strlen(s) + 1;
	char *const		dup = ft_memcpy(calloc_safe(len, sizeof(char)), s, len);
	char *const		val = ft_strchr(dup, '=');

	if (!val)
	{
		free(dup);
		*val_ptr = NULL;
		return (NULL);
	}
	*val = '\0';
	*val_ptr = val;
	return (dup);
}

t_list_var	*new_env_var_list(void)
{
	t_list_var	*list;
	char		**vec;
	char		*temp;
	char		*value;
	t_var_flags	attr;

	list = NULL;
	vec = environ;
	while (*vec)
	{
		temp = _make_pair(*vec, &value, '=');
		if (temp == NULL)
			exit(EXIT_FAILURE);
		attr = 0;
		set_flag(&attr, VF_EXPORTED);
		put_var(&list, temp, value, attr);
		free(temp);
		vec++;
	}
	return (list);
}

char	**var_list_to_str_vec(t_list_var *list)
{
	t_str_vec	*sv;
	t_str_buf	*sb;

	sv = NULL;
	while (list)
	{
		if (!list->value)
			continue ;
		sb = NULL;
		sb = str_append(sb, list->name);
		sb = str_append(sb, "=");
		sb = str_append(sb, list->value);
		sv = strv_append(sv, str_dispose(sb));
		list = list->next;
	}
	return (strv_dispose(sv));
}
