/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:42:44 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 22:39:00 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"
#include "string_vector.h"
#include "safe_io.h"
#include "minishell.h"

static int	is_all_digit(char *str)
{
	while (*str)
	{
		if (*str <= '0' || *str >= '9')
			return (-1);
		str++;
	}
	return (0);
}

static int	exit_print_error(int key, char *arg)
{
	if (key == EMPTY_CMD)
		return (print_error("exit", "parameter", "empty cmd", 1));
	else if (key == ERROR_OCCURED)
		return (print_error("exit", NULL, "too many arguments", 1));
	else if (key == FAST_DONE)
		return (print_error("exit", arg, "numeric argument required", 255));
	return (-1);
}

int	ft_exit(char **argv, t_env_list *env)
{
	size_t	size;

	(void)env;
	size = length_strvec(argv);
	if (!size)
		return (exit_print_error(EMPTY_CMD, NULL));
	putstr_safe("exit\n");
	if (size == 1)
		return (0);
	if (!is_all_digit(argv[1]))
	{
		if (size == 2)
			return (ft_atoi(argv[1]) & 255);
		else if (size > 2)
			return (exit_print_error(ERROR_OCCURED, argv[1]));
	}
	return (exit_print_error(FAST_DONE, argv[1]));
}
