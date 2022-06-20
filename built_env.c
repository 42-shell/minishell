/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:47:54 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 22:36:47 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "string_vector.h"

static size_t	env_print_error(int key)
{
	if (key == EMPTY_CMD)
		return (print_error("env", "parameter", "empty cmd", 1));
	else if (key == ERROR_OCCURED)
		return (print_error("env", "parameter", \
		"options or arguments found", 1));
	return (-1);
}

size_t	ft_env(char **argv, t_env_list *env)
{
	size_t	size;

	size = length_strvec(argv);
	if (!size)
		return (env_print_error(EMPTY_CMD));
	else if (length_strvec(argv) != 1)
		return (env_print_error(ERROR_OCCURED));
	print_env(env, NON_VISIBLE);
	return (0);
}
