/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:30:54 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 01:21:11 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include <stdlib.h>

void	ft_lstclear(t_env_list **lst)
{
	t_env_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content.id);
		free((*lst)->content.content);
		free(*lst);
		*lst = temp;
	}
}

static t_env_list	*ft_lstlast(t_env_list *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

static void	ft_lstadd_back(t_env_list **lst, t_env_list *new)
{
	if (new)
	{
		if (*lst)
			ft_lstlast(*lst)->next = new;
		else
			*lst = new;
	}
}

t_env_list	*ft_lstnew(char *id, char *content, t_env_list **head)
{
	t_env_list	*temp;

	temp = (t_env_list *)malloc(sizeof(t_env_list));
	if (!temp)
		return (NULL);
	temp->content.id = ft_strdup(id);
	temp->content.content = ft_strdup(content);
	temp->next = NULL;
	ft_lstadd_back(head, temp);
	return (temp);
}
