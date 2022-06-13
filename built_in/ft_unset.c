/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:24:04 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 15:49:57 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "env_module.h"

static void	ft_iter_unset(char *id, t_env_list **head)
{
	t_env_list	*lead;
	t_env_list	*follow;

	lead = (*head);
	follow = NULL;
	while (lead)
	{
		if(!ft_strcmp(id, lead->cotent.id))
		{
			if (follow)
				follow->next = lead->next;
			else
				(*head) = lead->next;
			ft_lstdel(lead);
			break ;
		}
		follow = lead;
		lead = lead->next;
	}
}

size_t	ft_unset(char **argv, t_env_list **head)
{
	size_t	size;

	size = ft_getarr_size(argv);
	if (!size || size == 1)
		return (-1);
	size = 1;
	while (argv[size])
	{
		ft_iter_unset(argv[size], head);
		size++;
	}
	return (0);
}
