/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_util_list_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:32:54 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 07:17:04 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "libft.h"
#include "safe_mem.h"
#include <stdlib.h> // malloc

static size_t	ft_compare(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2)
	{
		if (*s1 - *s2 > 0)
			return (1);
		else if (*s2 - *s1 > 0)
			return (0);
		else
		{
			s1++;
			s2++;
		}
	}
	if ((*s1 == '\0' && *s2 == '\0') || *s1 == '\0')
		return (0);
	return (1);
}

static void	ft_lstadd_sort_addon(t_env_list **lst, t_env_list *new_lst)
{
	t_env_list	*temp;
	t_env_list	*follow;

	temp = *lst;
	follow = NULL;
	while (temp)
	{
		if (ft_compare(temp->id, new_lst->id))
		{
			if (!follow)
			{
				new_lst->next = *lst;
				*lst = new_lst;
				return ;
			}
			new_lst->next = temp;
			follow->next = new_lst;
			return ;
		}
		follow = temp;
		temp = temp->next;
	}
	if (follow)
		follow->next = new_lst;
}

t_env_list	*ft_lstcpy(t_env_list *org, t_env_list **cpy)
{
	t_env_list	*temp;

	temp = (t_env_list *)malloc_safe(sizeof(t_env_list));
	temp->id = ft_strdup(org->id);
	temp->content = ft_strdup(org->content);
	temp->visible = org->visible;
	temp->next = NULL;
	if (!(*cpy))
		*cpy = temp;
	else
		ft_lstadd_sort_addon(cpy, temp);
	return (temp);
}
