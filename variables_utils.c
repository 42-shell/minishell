/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:32:39 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 11:43:50 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_flag.h"
#include "safe_mem.h"
#include "libft.h"
#include "string_buffer.h"
#include "string_vector.h"
#include "generic_list.h"

char	*alloc_str_pair(const char *s, char **val_ptr, char delim)
{
	const size_t	len = ft_strlen(s) + 1;
	char *const		dup = ft_memcpy(calloc_safe(len, sizeof(char)), s, len);
	char *const		val = ft_strchr(dup, delim);

	if (!val)
	{
		free(dup);
		*val_ptr = NULL;
		return (NULL);
	}
	*val = '\0';
	*val_ptr = val + 1;
	return (dup);
}

t_list_var	*strvec_to_var_list(char **arr)
{
	t_list_var	*list;
	char		**vec;
	char		*temp;
	char		*value;
	int			attr;

	list = NULL;
	vec = arr;
	while (*vec)
	{
		temp = alloc_str_pair(*vec, &value, '=');
		attr = 0;
		set_flag(&attr, VF_EXPORTED);
		if (temp)
			put_var(&list, temp, value, attr);
		else
			put_var(&list, *vec, NULL, attr);
		free(temp);
		vec++;
	}
	return (list);
}

char	**var_list_to_strvec(t_list_var *list)
{
	t_str_vec	*vec;
	t_str_buf	*buf;

	vec = NULL;
	while (list)
	{
		if (list->value)
			buf = str_append_format(NULL, "%s=%s", list->name, list->value);
		else
			buf = str_append(NULL, list->name);
		vec = strv_append(vec, str_dispose(buf));
		list = list->next;
	}
	return (strv_dispose(vec));
}

static int	_clear_v_list(t_list_var *elem)
{
	free(elem->name);
	free(elem->value);
	free(elem);
	return (0);
}

void	dispose_var_list(t_list_var *list)
{
	list_walk((void *)list, _clear_v_list);
}
