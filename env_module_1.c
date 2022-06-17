/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:49:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/18 02:05:06 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "libft.h" // strchr, strcmp, strdup
#include <stdlib.h> // free

void	clear_env(t_env_list **env)
{
	t_env_list	**temp;

	temp = env;
	ft_lstclear(temp);
	(*env) = NULL;
}

size_t	change_env(t_env_list *env, char *id, char *content)
{
	while (env)
	{
		if (!ft_strcmp(id, env->content.id))
		{
			free(env->content.content);
			env->content.content = ft_strdup(content);
			return (0);
		}
		env = env->next;
	}
	return (-1);
}

char	*get_env(t_env_list *env, char *id)
{
	while (env)
	{
		if (!ft_strcmp(id, env->content.id))
			return (env->content.content);
		env = env->next;
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
