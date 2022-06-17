/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_cpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:32:54 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/17 16:12:04 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "libft.h"
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

static void	ft_lstadd_sort_addon(t_env_list **lst, t_env_list *new)
{
	t_env_list	*temp;
	t_env_list	*follow;

	temp = *lst;
	follow = NULL;
	while (temp)
	{
		if (ft_compare(temp->content.id, new->content.id))
		{
			if (!follow)
			{
				new->next = *lst;
				*lst = new;
				return ;
			}
			new->next = temp;
			follow->next = new;
			return ;
		}
		follow = temp;
		temp = temp->next;
	}
	if (follow)
		follow->next = new;
}

t_env_list	*ft_lstcpy(t_env_list *org, t_env_list **cpy)
{
	t_env_list	*temp;

	temp = (t_env_list *)malloc(sizeof(t_env_list));
	if (!temp)
		return (NULL);
	temp->content.id = ft_strdup(org->content.id);
	temp->content.content = ft_strdup(org->content.content);
	temp->content.visible = org->content.visible;
	temp->next = NULL;
	if (!(*cpy))
		*cpy = temp;
	else
		ft_lstadd_sort_addon(cpy, temp);
	return (temp);
}
