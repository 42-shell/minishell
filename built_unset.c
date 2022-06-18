/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:24:04 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/18 19:45:42 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"

size_t	ft_unset(char **argv, t_env_list **env)
{
	size_t		size;

	size = ft_getarr_size(argv);
	if (!size || size == 1)
		return (-1);
	size = 1;
	while (argv[size])
	{
		del_env(argv[size], env);
		size++;
	}
	return (0);
}
