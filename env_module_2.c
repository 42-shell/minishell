/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:45:21 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/18 20:19:41 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "libft.h" // strcmp

int	add_env(t_env_list *env, char *id, char *content, int key)
{
	if (!ft_lstnew(id, content, &env, key))
		return (-1);
	return (0);
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
