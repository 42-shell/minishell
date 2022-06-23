/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:32:39 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 05:44:15 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_flag.h"
#include "safe_mem.h"
#include "libft.h"
#include "string_buffer.h"
#include "string_vector.h"
#include "generic_list.h"

extern char	**environ;

static char	*_alloc_pair(const char *s, char **val_ptr, char delim)
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

t_list_var	*new_env_var_list(void)
{
	t_list_var	*list;
	char		**vec;
	char		*temp;
	char		*value;
	int			attr;

	list = NULL;
	vec = environ;
	while (*vec)
	{
		temp = _alloc_pair(*vec, &value, '=');
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

char	**var_list_to_strvec(t_list_var *list)
{
	t_str_vec	*vec;
	t_str_buf	*buf;

	vec = NULL;
	while (list)
	{
		if (!list->value)
			continue ;
		buf = str_append_format(NULL, "%s=%s", list->name, list->value);
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
