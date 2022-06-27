/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils_sort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:32:39 by jkong             #+#    #+#             */
/*   Updated: 2022/06/28 02:58:48 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "string_vector.h"

t_list_var	*clone_var_list(t_list_var *list)
{
	t_list_var	*new_list;

	new_list = NULL;
	while (list)
	{
		put_var(&new_list, list->name, list->value, list->attr);
		list = list->next;
	}
	return (new_list);
}

static int	_compare_var_list(t_list_var *a, t_list_var *b)
{
	return (ft_strcmp(a->name, b->name));
}

static void	_swap_var_list(t_list_var *a, t_list_var *b)
{
	char *const			x_name = a->name;
	char *const			x_value = a->value;
	const t_var_flags	x_attr = a->attr;

	a->name = b->name;
	a->value = b->value;
	a->attr = b->attr;
	b->name = x_name;
	b->value = x_value;
	b->attr = x_attr;
}

t_list_var	*sort_var_list(t_list_var *list)
{
	t_list_var	*it;
	t_list_var	*next;

	it = list;
	while (it && it->next)
	{
		next = it->next;
		while (next)
		{
			if (_compare_var_list(it, next) > 0)
				_swap_var_list(it, next);
			next = next->next;
		}
		it = it->next;
	}
	return (list);
}
