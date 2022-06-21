/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:41:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 16:22:03 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "env_module.h"
#include "libft.h"
#include "string_vector.h"
#include <unistd.h>

static int	_assert_param(size_t argc, char **argv, t_env_list *env)
{
	char 	*str;

	if (argc > 1)
		str = argv[1];
	else
		str = "~";
	if (ft_strcmp(str, "~") == 0 && chdir(get_env(env, "HOME") < 0))
		return (0);
	else if (ft_strcmp(str, "-") == 0 && chdir(get_env(env, "OLDPWD")) < 0)
		return (0);
	else if (argc <= 1 || chdir(str) < 0)
		return (0);
	return (1);
}

static void	_change_pwd(t_env_list *env)
{
	char *const	cwd = getcwd(NULL, 0);

	if (!cwd)
		exit(EXIT_FAILURE);
	change_env(env, "OLDPWD", get_env(env, "PWD"));
	change_env(env, "PWD", cwd);
	free(cwd);
}

int	ft_cd(char **argv, t_env_list **env)
{
	const size_t	argc = length_strvec(argv);

	if (!_assert_param(argc, argv, *env))
	{
		if (argc > 1)
			built_in_print_error("cd", argv[1], "failure");
		else
			built_in_print_error("cd", NULL, "failure");
		return (EXIT_FAILURE);
	}
	_change_pwd(*env);
	return (EXIT_SUCCESS);
}
