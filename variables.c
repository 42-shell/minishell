/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:32:39 by jkong             #+#    #+#             */
/*   Updated: 2022/06/25 13:13:03 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_mem.h"
#include "libft.h"
#include "generic_list.h"

static char	*_strdup(const char *s)
{
	const size_t	len = ft_strlen(s) + 1;

	return (ft_memcpy(calloc_safe(len, sizeof(char)), s, len));
}

static int	_compare_var_name(t_list_var *item, char *name)
{
	return (ft_strcmp(item->name, name));
}

char	*get_var(t_list_var *list, char *name)
{
	while (list)
	{
		if (_compare_var_name(list, name) == 0)
			return (list->value);
		list = list->next;
	}
	return (NULL);
}

void	put_var(t_list_var **list_ptr, char *name, char *value,
	t_var_flags attr)
{
	t_list_var	*list;

	list = *list_ptr;
	while (list)
	{
		if (_compare_var_name(list, name) == 0)
		{
			if (value)
			{
				free(list->value);
				list->value = _strdup(value);
			}
			return ;
		}
		list = list->next;
	}
	list = calloc_safe(1, sizeof(*list));
	list->name = _strdup(name);
	if (value)
		list->value = _strdup(value);
	list->attr = attr;
	list_append((void *)list_ptr, (void *)list);
}

void	unset_var(t_list_var **list_ptr, char *name)
{
	t_list_var	*list;

	list = (void *)list_remove((void *)list_ptr, _compare_var_name, name);
	if (!list)
		return ;
	free(list->name);
	free(list->value);
	free(list);
}
