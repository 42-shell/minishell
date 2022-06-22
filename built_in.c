/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 08:02:17 by jkong             #+#    #+#             */
/*   Updated: 2022/06/22 11:50:31 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "safe_io.h"
#include "string_buffer.h"
#include "libft.h"
#include <string.h>
#include <errno.h>

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

void	built_in_print_error(char *cmd, char *param, char *cause)
{
	t_str_buf	*sb;
	char		*temp;

	sb = str_append(NULL, "minishell: ");
	if (cmd)
		sb = str_append(str_append(sb, cmd), ": ");
	if (param)
		sb = str_append(str_append(sb, param), ": ");
	if (errno != 0)
	{
		if (cause || !cause)
			cause = strerror(errno);
		errno = 0;
	}
	sb = str_append(str_append(sb, temp), "\n");
	temp = str_dispose(sb);
	puterr_safe(temp);
	free(temp);
}
