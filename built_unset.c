/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:24:04 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/19 02:55:23 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"

static size_t	unset_check_error(t_env_list *env, size_t check_error)
{
	if (check_error)
	{
		change_env(env, "EXIT_STATUS", "1");
		return (-1);
	}
	else
	{
		change_env(env, "EXIT_STATUS", "0");
		return (0);
	}
}

static size_t	unset_print_error(int key, t_env_list *env)
{
	if (key == EMPTY_CMD)
	{
		change_env(env, "EXIT_STATUS", "1");
		return (print_error("unset", "parameter", "empty cmd"));
	}
	else if (key == FAST_DONE)
	{
		change_env(env, "EXIT_STATUS", "0");
		return (0);
	}
	return (-1);
}

size_t	ft_unset(char **argv, t_env_list **env)
{
	size_t	size;
	size_t	check_error;

	size = ft_getarr_size(argv);
	if (!size)
		return (unset_print_error(EMPTY_CMD, *env));
	else if (size == 1)
		return (unset_print_error(FAST_DONE, *env));
	size = 1;
	check_error = 0;
	while (argv[size])
	{
		del_env(argv[size], env);
		if (env_syntax_check(argv[size], SKIP_ON))
		{
			check_error++;
			print_error("unset", argv[size], "not a valid identifier");
		}
		else
			del_env(argv[size], env);
		size++;
	}
	return (unset_check_error(*env, check_error));
}
