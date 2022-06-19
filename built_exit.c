/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:42:44 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/19 21:52:04 by yongmkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"
#include "safe_io.h"
#include "minishell.h"

static int	is_all_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		str++;
	}
	return (0);
}

// if return -1, then doesn't exit minishell
static int	exit_print_error(int key, t_env_list *env)
{
	change_env(env, "EXIT_STATUS", "1");
	if (key == EMPTY_CMD)
		return (print_error("exit", "parameter", "empty cmd"));
	else if (key == ERROR_OCCURED)
		return (print_error("exit", NULL, "too many arguments"));
	return (-1);
}

int	ft_exit(char **argv, t_env_list *env)
{
	size_t	size;
	size_t	atoi;

	change_late_cmd(env, "exit", BUILT_IN);
	size = ft_getarr_size(argv);
	if (!size)
		return (exit_print_error(EMPTY_CMD, env));
	putstr_safe("exit\n");
	if (size == 1)
		return (0);
	if (!is_all_digit(argv[1]))
	{
		if (size == 2)
			return (ft_atoi(argv[1]) & 255);
		else if (size > 2)
			return (exit_print_error(ERROR_OCCURED, env));
	}
	else
		print_error("exit", argv[1], "numeric argument required");
	return (255);
}
