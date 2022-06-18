/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:45:21 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/19 02:43:47 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "minishell.h"
#include "libft.h" // strcmp

void	add_env(t_env_list *env, char *id, char *content, int key)
{
	ft_lstnew(id, content, &env, key);
}

void	del_env(char *id, t_env_list **env)
{
	t_env_list	*lead;
	t_env_list	*follow;

	lead = (*env);
	follow = NULL;
	while (lead)
	{
		if (!ft_strcmp(id, lead->content.id))
		{
			if (follow)
				follow->next = lead->next;
			else
				(*env) = lead->next;
			ft_lstdel(lead);
			break ;
		}
		follow = lead;
		lead = lead->next;
	}
}

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
