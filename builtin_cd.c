/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:25 by jkong             #+#    #+#             */
/*   Updated: 2022/06/25 13:39:29 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "safe_io.h"
#include "libft.h"
#include "string_vector.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>

static char	*_get_env_path(t_list_var *env, char *name)
{
	char *const	value = get_var(env, name);

	if (!value)
		print_err("cd: %s not set\n", name);
	return (value);
}

static char	*_get_pwd(size_t argc, char **argv, t_list_var **envp)
{
	char	*str;

	if (argc <= 1)
		str = _get_env_path(*envp, "HOME");
	else if (ft_strcmp(argv[1], "-") == 0)
		str = _get_env_path(*envp, "OLDPWD");
	else
		str = argv[1];
	return (str);
}

static int	_setenv(size_t argc, char **argv, t_list_var **envp)
{
	char *const	cwd = getcwd(NULL, 0);

	if (!cwd)
		return (0);
	if (argc > 1 && ft_strcmp(argv[1], "-") == 0)
		printf("%s\n", get_var(*envp, "OLDPWD"));
	put_var(envp, "OLDPWD", get_var(*envp, "PWD"), VFV_EXPORTED);
	put_var(envp, "PWD", cwd, VFV_EXPORTED);
	free(cwd);
	return (1);
}

t_builtin_res	ft_cd(t_builtin_argv argv, t_builtin_envp envp)
{
	const size_t	argc = length_strvec(argv);
	char *const		pwd = _get_pwd(argc, argv, envp);

	if (!pwd)
		return (EXIT_FAILURE);
	if ((ft_strlen(pwd) != 0 && chdir(pwd) < 0) || !_setenv(argc, argv, envp))
	{
		if (argc > 1)
			print_err("cd: %s: %s\n", argv[1], strerror(errno));
		else
			print_err("cd: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
