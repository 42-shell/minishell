/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:41:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/19 12:05:16 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "env_module.h"
#include "libft.h" // getarr_size
#include <unistd.h> // chdir

static size_t	cd_print_error(char *parameter, int key, t_env_list *env)
{
	change_env(env, "EXIT_STATUS", "1");
	if (key == EMPTY_CMD)
		return (print_error("cd", "parameter", "empty cmd"));
	else if (key == ERROR_OCCURED)
		return (print_error("cd", parameter, "failure"));
	return (-1);
}

static size_t	check_tild_dash(char **argv, t_env_list *env, int size)
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

static void	cd_change_pwd(t_env_list *env)
{
	char	*id;

	change_env(env, "OLDPWD", get_env(env, "PWD"));
	id = ft_get_pwd();
	change_env(env, "PWD", id);
	free(id);
	change_env(env, "EXIT_STATUS", "0");
}

size_t	ft_cd(char **argv, t_env_list *env)
{
	int		size;

	change_late_cmd(env, "cd", BUILT_IN);
	size = ft_getarr_size(argv);
	if (!size)
		return (cd_print_error(NULL, EMPTY_CMD, env));
	else if (check_tild_dash(argv, env, size))
		return (cd_print_error(argv[1], ERROR_OCCURED, env));
	cd_change_pwd(env);
	return (0);
}
