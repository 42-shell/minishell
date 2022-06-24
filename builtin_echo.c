/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:25 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 22:22:59 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "safe_io.h"
#include "string_buffer.h"
#include "string_vector.h"

static char	**_process_option(char **argv, int *display_return)
{
	char	*str;

	argv++;
	*display_return = 1;
	while (*argv)
	{
		str = *argv;
		if (*str++ == '-' && *str != '\0')
		{
			while (*str == 'n')
			{
				if (*str == 'n')
					*display_return = 0;
				str++;
			}
			if (*str != '\0' && *str != 'n')
				break ;
		}
		else
			break ;
		argv++;
	}
	return (argv);
}

t_builtin_res	ft_echo(t_builtin_argv argv, t_builtin_envp envp)
{
	int			display_return;
	char		**value;
	t_str_buf	*buf;
	char		*str;

	(void)envp;
	value = _process_option(argv, &display_return);
	buf = NULL;
	while (*value)
	{
		buf = str_append(buf, *value++);
		if (*value)
			buf = str_append(buf, " ");
	}
	if (display_return)
		buf = str_append(buf, "\n");
	str = str_dispose(buf);
	if (str)
		putstr_safe(str);
	free(str);
	return (EXIT_SUCCESS);
}
