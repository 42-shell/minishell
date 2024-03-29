/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:25 by jkong             #+#    #+#             */
/*   Updated: 2022/06/25 14:35:44 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "util_try_atoi.h"
#include "safe_io.h"
#include "string_vector.h"

t_builtin_res	ft_exit(t_builtin_argv argv, t_builtin_envp envp)
{
	const size_t	argc = length_strvec(argv);
	int				status;

	(void)&argv;
	(void)&envp;
	if (isatty(STDIN_FILENO))
		putstr_safe("exit\n");
	if (argc == 1)
		status = g_exit_status;
	else if (!try_atoi(argv[1], &status))
	{
		status = EX_BADUSAGE;
		print_err("exit: numeric argument required\n");
	}
	else if (argc > 2)
	{
		print_err("exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	exit(status & 0xFF);
}
