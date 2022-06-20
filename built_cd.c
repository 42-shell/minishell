/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:41:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 15:59:21 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "env_module.h"
#include "libft.h" // getarr_size
#include <unistd.h> // chdir

static size_t	cd_print_error(char *parameter, int key, t_env_list *env)
{
	if (key == EMPTY_CMD)
		return (print_error("cd", "parameter", "empty cmd", 1));
	else if (key == ERROR_OCCURED)
		return (print_error("cd", parameter, "failure", 1));
	else
		return (-1);
}

static size_t	check_path(char **argv, t_env_list *env, int size)
{
	if ((size == 1 || !ft_strcmp(argv[1], "~")) \
	&& chdir(get_env(env, "HOME")))
		return (-1);
	else if (!ft_strcmp(argv[1], "-") && chdir(get_env(env, "OLDPWD")))
		return (-1);
	else if (chdir(argv[1]))
		return (-1);
	return (0);
}

static size_t	cd_change_pwd(t_env_list *env)
{
	char	*id;

	change_env(env, "OLDPWD", get_env(env, "PWD"));
	id = ft_get_pwd();
	change_env(env, "PWD", id);
	free(id);
	return (0);
}

size_t	ft_cd(char **argv, t_env_list *env)
{
	int		size;

	size = ft_getarr_size(argv);
	if (!size)
		return (cd_print_error(NULL, EMPTY_CMD, env));
	else if (check_path(argv, env, size))
		return (cd_print_error(argv[1], ERROR_OCCURED, env));
	return (cd_change_pwd(env));
}
