/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:49:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/15 17:48:41 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "libft.h" // strchr, strcmp, strdup
#include <stdlib.h> // free

void	clear_env(t_env_list **head)
{
	t_env_list	**temp;

	temp = head;
	ft_lstclear(temp);
	(*head) = NULL;
}

size_t	change_env(t_env_list *head, char *id, char *content)
{
	while (head)
	{
		if (!ft_strcmp(id, head->content.id))
		{
			free(head->content.content);
			head->content.content = ft_strdup(content);
			return (0);
		}
		head = head->next;
	}
	return (-1);
}

char	*get_env(t_env_list *head, char *id)
{
	while (head)
	{
		if (!ft_strcmp(id, head->content.id))
			return (head->content.content);
		head = head->next;
	}
	return (NULL);
}

t_env_list	*set_env(char **env)
{
	t_env_list	*head;
	t_env_list	*temp;
	char		*pos;

	head = NULL;
	while (env && *env)
	{
		pos = ft_strchr(*env, '=');
		if (pos)
		{
			(*env)[pos - *env] = '\0';
			temp = ft_lstnew(*env, &(*env)[pos - *env + 1], &head, ON_VISIBLE);
			if (!temp)
			{
				clear_env(&head);
				return (NULL);
			}
		}
		else
			break ;
		env++;
	}
	return (head);
}
