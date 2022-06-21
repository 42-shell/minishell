/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:24:04 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 16:47:16 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "string_vector.h"

// asd

int	ft_unset(char **argv, t_env_list **env)
{
	size_t	size;
	int		err;

	size = length_strvec(argv);
	if (size == 1)
		return (EXIT_SUCCESS);
	size = 1;
	err = 0;
	while (argv[size])
	{
		del_env(argv[size], env);
		if (env_syntax_check(argv[size], 1))
		{
			err |= 1;
			built_in_print_error("unset", argv[size], "not a valid identifier");
			// exit(EXIT_FAILURE); // Save to last command exit status
		}
		else
			del_env(argv[size], env);
		size++;
	}
	return (err);
}
