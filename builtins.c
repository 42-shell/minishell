/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:25 by jkong             #+#    #+#             */
/*   Updated: 2022/06/23 23:24:48 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

static const t_builtin_info	g_builtins[] = {
	(t_builtin_info){"echo", &ft_echo},
	(t_builtin_info){"cd", &ft_cd},
	(t_builtin_info){"pwd", &ft_pwd},
	(t_builtin_info){"export", &ft_export},
	(t_builtin_info){"unset", &ft_unset},
	(t_builtin_info){"env", &ft_env},
	(t_builtin_info){"exit", &ft_exit},
	(t_builtin_info){NULL, NULL},
};

t_builtin_func	get_builtin(char *cmd)
{
	size_t	i;

	i = 0;
	while (g_builtins[i].key)
	{
		if (ft_strcmp(g_builtins[i].key, cmd) == 0)
			break ;
		i++;
	}
	return (g_builtins[i].pfn);
}
