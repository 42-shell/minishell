/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:50:49 by jkong             #+#    #+#             */
/*   Updated: 2022/06/14 16:37:01 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_list.h"

void	list_walk(t_generic_list *list, t_gl_func *func)
{
	while (list)
	{
		if ((*func)(list) < 0)
			break ;
		list = list->next;
	}
}

t_generic_list	*list_reverse(t_generic_list *list)
{
	t_generic_list	*next;
	t_generic_list	*reverse_head;

	reverse_head = NULL;
	while (list)
	{
		next = list->next;
		list->next = reverse_head;
		reverse_head = list;
		list = next;
	}
	return (reverse_head);
}

size_t	list_length(t_generic_list *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	list_append(t_generic_list **head, t_generic_list *elem)
{
	t_generic_list	*t;

	if (!*head)
		*head = elem;
	else if (elem)
	{
		t = *head;
		while (t->next)
			t = t->next;
		t->next = elem;
	}
}

t_generic_list	*list_remove(t_generic_list **list, t_gl_func *cmp, void *arg)
{
	t_generic_list	*prev;
	t_generic_list	*t;

	prev = NULL;
	t = *list;
	while (t)
	{
		if ((*cmp)(t, arg))
		{
			if (prev)
				prev->next = t->next;
			else
				*list = t->next;
			break ;
		}
		prev = t;
		t = t->next;
	}
	return (t);
}
