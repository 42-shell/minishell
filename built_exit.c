/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:42:44 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 16:49:48 by yongmkim         ###   ########.fr       */
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

static int	exit_print_error(int key, t_env_list *env)
{
	if (key == EMPTY_CMD)
		return (print_error("exit", "parameter", "empty cmd", 1));
	else if (key == ERROR_OCCURED)
		return (print_error("exit", NULL, "too many arguments", 1));
	else if (key == FAST_DONE)
		return (print_error("exit", argv[1], "numeric argument required", 255));
	return (-1);
}

int	ft_exit(char **argv, t_env_list *env)
{
	size_t	size;

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
		return (exit_print_error(FAST_DONE, env));
}
