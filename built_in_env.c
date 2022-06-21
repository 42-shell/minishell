/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:47:54 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 16:09:59 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "string_vector.h"

int	ft_env(char **argv, t_env_list **env)
{
	if (length_strvec(argv) != 1)
	{
		built_in_print_error("env", "parameter", "options or arguments found");
		return (EXIT_FAILURE);
	}
	print_env(*env, NON_VISIBLE);
	return (EXIT_SUCCESS);
}
