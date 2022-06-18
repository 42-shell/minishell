/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:41:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/18 17:54:37 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h" // getarr_size
#include <unistd.h> // chdir

static size_t	check_tild_dash(char **argv, t_env_list *env)
{
	if (ft_strcmp(argv[1], "-"))
	{
		if (chdir(get_env(env, "OLDPWD")))
			return (-1);
	}
	else if (ft_strcmp(argv[1], "~"))
	{
		if (chdir(get_env(env, "HOME")))
			return (-1);
	}
	else if (chdir(argv[1]))
		return (-1);
	return (0);
}

size_t	ft_cd(char **argv, t_env_list *env)
{
	int		size;
	char	*id;

	size = ft_getarr_size(argv);
	if (!size || size > 2)
		return (-1);
	if (size == 1)
	{
		id = get_env(env, "HOME");
		if (!id || chdir(id))
			return (-1);
	}
	else if (size == 2)
	{
		if (check_tild_dash(argv, env))
			return (-1);
	}
	change_env(env, "OLDPWD", get_env(env, "PWD"));
	id = ft_get_pwd();
	change_env(env, "PWD", id);
	free(id);
	return (0);
}
