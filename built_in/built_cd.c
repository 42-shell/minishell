/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:41:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 21:23:09 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include <unistd.h>

static size_t	ft_getsize_argv(char **argv)
{
	int	i;

	if (!argv || !(*argv))
		return (0);
	i = 0;
	while (argv[i])
		i++;
	return (i);
}

size_t	ft_cd(char **argv)
{
	int	size;

	size = ft_getsize_argv(argv);
	if (size == 0 || size > 2)
		return (-1);
	else if (chdir(argv[1]))
		return (-1);
	return (0);
}
