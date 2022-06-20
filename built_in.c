/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 08:02:17 by jkong             #+#    #+#             */
/*   Updated: 2022/06/21 08:10:20 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"

static const t_built_in_info	g_built_ins[] = {
	(t_built_in_info){"pwd", &ft_pwd},
	(t_built_in_info){"echo", &ft_echo},
	(t_built_in_info){"cd", &ft_cd},
	(t_built_in_info){"env", &ft_env},
	(t_built_in_info){"export", &ft_export},
	(t_built_in_info){"unset", &ft_unset},
	(t_built_in_info){"exit", &ft_exit},
	(t_built_in_info){NULL, NULL},
};

t_built_in_func	get_built_in(char *cmd)
{
	size_t	i;

	i = 0;
	while (g_built_ins[i].key)
	{
		if (ft_strcmp(g_built_ins[i].key, cmd) == 0)
			break ;
		i++;
	}
	return (g_built_ins[i].pfn);
}
