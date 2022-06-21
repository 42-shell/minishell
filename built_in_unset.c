/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:24:04 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 16:25:30 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "string_vector.h"

asd

static int	unset_print_error(int key, char *arg)
{
	if (key == EMPTY_CMD)
		return (print_error("unset", "parameter", "empty cmd", 1));
	else if (key == FAST_DONE)
		return (0);
	else if (key == ERROR_OCCURED)
		return (print_error("unset", arg, "not a valid identifier", 1));
	return (-1);
}

int	ft_unset(char **argv, t_env_list **env)
{
	size_t	size;
	int		err;

	size = length_strvec(argv);
	if (size == 1)
		return (unset_print_error(FAST_DONE, NULL));
	size = 1;
	err = 0;
	while (argv[size])
	{
		del_env(argv[size], env);
		if (env_syntax_check(argv[size], 1))
		{
			err |= 1;
			unset_print_error(ERROR_OCCURED, argv[size]);
		}
		else
			del_env(argv[size], env);
		size++;
	}
	return (err);
}
