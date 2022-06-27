/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:25 by jkong             #+#    #+#             */
/*   Updated: 2022/06/28 02:44:38 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "safe_io.h"
#include "util_flag.h"
#include "string_buffer.h"

t_builtin_res	ft_env(t_builtin_argv argv, t_builtin_envp envp)
{
	t_list_var	*list;
	t_str_buf	*buf;
	char		*str;

	(void)&argv;
	list = *envp;
	buf = NULL;
	while (list)
	{
		if (has_flag(list->attr, VF_EXPORTED) && list->value)
			buf = str_append_format(buf, "%s=%s\n", list->name, list->value);
		list = list->next;
	}
	str = str_dispose(buf);
	putstr_safe(str);
	free(str);
	return (EXIT_SUCCESS);
}
