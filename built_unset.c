/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:24:04 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 16:42:03 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"

static size_t	unset_print_error(int key, t_env_list *env)
{
	if (key == EMPTY_CMD)
		return (print_error("unset", "parameter", "empty cmd", 1));
	else if (key == FAST_DONE)
		return (0);
	else if (key == ERROR_OCCURED)
		print_error("unset", argv[size], "not a valid identifier");
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
			unset_print_error(ERROR_OCCURED, *env);
		}
		else
			del_env(argv[size], env);
		size++;
	}
	return (check_error > 0);
}
