/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:49:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/19 21:59:33 by yongmkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "libft.h" // strchr, strcmp, strdup
#include <stdlib.h> // free
#include "minishell.h"

int	env_syntax_check(char *str, int skip_equal)
{
	if (!str || *str == '\0')
		return (-1);
	else if (legal_variable_starter(*str))
		str++;
	else
		return (-1);
	while (*str)
	{
		if (legal_variable_char(*str))
			str++;
		else if (!skip_equal && *str == '=')
			return (0);
		else
			return (-1);
	}
	return (0);
}

void	clear_env(t_env_list **env)
{
	t_env_list	**temp;

	temp = env;
	ft_lstclear(temp);
	(*env) = NULL;
}

int	change_env(t_env_list *env, char *id, char *content)
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
	return (0);
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
		}
		else
			break ;
		env++;
	}
	add_env(head, "EXIT_STATUS", "0", HIDE_VISIBLE);
	add_env(head, "MINISHELL_INIT_PATH", get_env(head, "PWD"), HIDE_VISIBLE);
	return (head);
}
