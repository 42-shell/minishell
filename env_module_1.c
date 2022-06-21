/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:49:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 15:29:44 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "libft.h" // strchr, strcmp, strdup
#include <stdlib.h> // free
#include "minishell.h"
#include "string_buffer.h"

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

int	change_env(t_env_list *env, char *id, char *content)
{
	while (env)
	{
		if (!ft_strcmp(id, env->id))
		{
			free(env->content);
			env->content = ft_strdup(content);
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
		if (!ft_strcmp(id, env->id))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

t_env_list	*set_env(char **env)
{
	t_env_list	*head;
	char		*pos;

	head = NULL;
	while (env && *env)
	{
		pos = ft_strchr(*env, '=');
		if (pos)
		{
			(*env)[pos - *env] = '\0';
			ft_lstnew(*env, &(*env)[pos - *env + 1], &head, ON_VISIBLE);
		}
		else
			break ;
		env++;
	}
	return (head);
}
