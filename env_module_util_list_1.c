/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_default.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:30:54 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/17 16:12:28 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "libft.h"
#include <stdlib.h> // malloc, free

void	ft_lstdel(t_env_list *lst)
{
	free(lst->content.id);
	free(lst->content.content);
	free(lst);
	lst = NULL;
}

void	ft_lstclear(t_env_list **lst)
{
	t_env_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdel(*lst);
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

void	ft_lstadd_back(t_env_list **lst, t_env_list *new)
{
	if (new)
	{
		if (*lst)
			ft_lstlast(*lst)->next = new;
		else
			*lst = new;
	}
}

t_env_list	*ft_lstnew(char *id, char *content, t_env_list **head, int key)
{
	t_env_list	*temp;

	temp = (t_env_list *)malloc(sizeof(t_env_list));
	if (!temp)
		return (NULL);
	temp->content.id = ft_strdup(id);
	temp->content.content = ft_strdup(content);
	temp->content.visible = key;
	temp->next = NULL;
	ft_lstadd_back(head, temp);
	return (temp);
}