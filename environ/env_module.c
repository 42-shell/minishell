/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:49:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 12:59:07 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"



#include <stdio.h> // test
#include <stdlib.h> // test
// add find path, oldpwd, home
// clear env_list
	
void	clear_env(t_env_list *head)
{
	ft_lstclear(&head);
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



//////////////////////////////////////////////////////////////////////
void check(void)
{
	system("leaks a.out");
}

int main(int argc, char **argv, char **envp)
{
	int			i = 0;
	t_env_list	*head;
	t_env_list	*temp;

	//atexit(check);
	head = set_env(envp);
	temp = head;
	while (temp)
	{
		printf("iD  : %s\n", temp->content.id);
		printf("CTX : %s\n\n", temp->content.content);
		temp = temp->next;
	}
	printf("---\n");
	printf("%s\n", get_env(head, "PATH"));
	printf("%s\n", get_env(head, "PAT"));
	printf("---\n");
	clear_env(head);
	return (0);
}