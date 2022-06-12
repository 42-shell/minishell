/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:49:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 01:23:45 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include <stddef.h>



#include <stdio.h> // test
#include <stdlib.h> // test
// add find path, oldpwd, home
// clear env_list
//

t_env_list	*env_set(char **env)
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
			temp = ft_lstnew(*env, &(*env)[pos - *env + 1], &head);
			if (!temp)
			{
				ft_lstclear(&head);
				return (NULL);
			}
		}
		else
			break ;
		env++;
	}
	return (head);
}


void check(void)
{
	system("leaks a.out");
}

int main(int argc, char **argv, char **envp)
{
	int			i = 0;
	t_env_list	*head;
	t_env_list	*temp;
	t_env_list	*org;

	atexit(check);
	head = env_set(envp);
	org = head;
	while (head)
	{
		temp = head->next;
		printf("iD  : %s\n", head->content.id);
		printf("CTX : %s\n\n", head->content.content);
		head = temp;
	}
	ft_lstclear(&org);
	return (0);
}
