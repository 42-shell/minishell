/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:25 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 00:35:40 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "string_buffer.h"
#include "string_vector.h"
#include "safe_io.h"

static char	**_process_option(char **argv, int *display_return)
{
	char	*str;

	argv++;
	*display_return = 1;
	while (*argv)
	{
		str = *argv;
		if (*str++ == '-')
		{
			while (*str == 'n')
			{
				if (*str == 'n')
					*display_return = 0;
				str++;
			}
			if (*str != '\0')
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
	t_str_buf	*sb;
	char		*temp;

	(void)envp;
	value = _process_option(argv, &display_return);
	sb = NULL;
	while (*value)
	{
		sb = str_append(sb, *value++);
		if (*value)
			sb = str_append(sb, " ");
	}
	if (display_return)
		sb = str_append(sb, "\n");
	temp = str_dispose(sb);
	if (temp)
		putstr_safe(temp);
	free(temp);
	return (EXIT_SUCCESS);
}
