/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:41:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/16 19:18:33 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h" // getarr_size
#include <unistd.h> // chdir

static size_t	check_tild_dash(char **argv, t_env_list *head)
{
	if (ft_strcmp(argv[1], "-", 1))
	{
		if (chdir(get_env(head, "OLDPWD")))
			return (-1);
	}
	else if (ft_strcmp(argv[1], "~", 1))
	{
		if (chdir(get_env(head, "HOME")))
			return (-1);
	}
	else if (chdir(argv[1]))
		return (-1);
	return (0);
}

size_t	ft_cd(char **argv, t_env_list *head)
{
	int		size;
	char	*id;

	size = ft_getarr_size(argv);
	if (!size || size > 2)
		return (-1);
	if (size == 1)
	{
		id = get_env(head, "HOME");
		if (!id)
			return (-1);
		else if (chdir(id))
			return (-1);
	}
	else if (size == 2)
	{
		if (check_tild_dash(argv, head))
			return (-1);
	}
	return (change_env(head, "OLDPWD", get_env(head, "PWD")));
}
