/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:42:44 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 16:20:50 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"
#include "string_vector.h"
#include "safe_io.h"
#include "minishell.h"

static int	_isnumeric(char *str)
{
	while (*str)
	{
		if (*str <= '0' || *str >= '9')
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(char **argv, t_env_list **env)
{
	size_t	size;
	int		status;

	(void)env;
	size = length_strvec(argv);
	putstr_safe("exit\n");
	if (size == 1)
		status = EXIT_SUCCESS;
	else if (!_isnumeric(argv[1]))
	{
		status = -1;
		built_in_print_error("exit", argv[1], "numeric argument required");
	}
	else
		status = ft_atoi(argv[1]);
	if (size > 2)
	{
		built_in_print_error("exit", NULL, "too many arguments");
		return (EXIT_FAILURE);
	}
	exit(status & 0xFF);
}
