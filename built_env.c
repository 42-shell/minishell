/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:47:54 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/19 02:49:50 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h" //getarr_size

static size_t	env_print_error(int key, t_env_list *env)
{
	change_env(env, "EXIT_STATUS", "1");
	if (key == EMPTY_CMD)
		return (print_error("env", "parameter", "empty cmd"));
	else if (key == ERROR_OCCURED)
		return (print_error("env", "parameter", "options or arguments found"));
	return (-1);
}

size_t	ft_env(char **argv, t_env_list *env)
{
	size_t	size;

	size = ft_getarr_size(argv);
	if (!size)
		return (env_print_error(EMPTY_CMD, env));
	else if (ft_getarr_size(argv) != 1)
		return (env_print_error(ERROR_OCCURED, env));
	print_env(env, NON_VISIBLE);
	change_env(env, "EXIT_STATUS", "0");
	return (0);
}
