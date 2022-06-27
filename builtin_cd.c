/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:25 by jkong             #+#    #+#             */
/*   Updated: 2022/06/28 01:04:08 by jkong            ###   ########.fr       */
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

static char	*_get_pwd(size_t argc, char **argv, t_list_var **envp, int *alert)
{
	char	*name;
	char	*path;

	*alert = 0;
	path = NULL;
	if (argc <= 1)
		name = _get_env_path(*envp, "HOME");
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		name = _get_env_path(*envp, "OLDPWD");
		*alert = 1;
	}
	else if (is_absolute_path(argv[1], 2))
		name = argv[1];
	else
	{
		name = argv[1];
		path = find_path(get_var(*envp, "CDPATH"), name, FS_PATHNAME);
		if (path)
			*alert = 1;
	}
	if (!path && name)
		path = resolve_path(NULL, name);
	return (path);
}

static int	_setenv(t_list_var **envp, int alert)
{
	char *const	cwd = getcwd(NULL, 0);

	if (!cwd)
		return (0);
	put_var(envp, "OLDPWD", get_var(*envp, "PWD"), VFV_EXPORTED);
	put_var(envp, "PWD", cwd, VFV_EXPORTED);
	if (alert)
		printf("%s\n", cwd);
	free(cwd);
	return (1);
}

t_builtin_res	ft_cd(t_builtin_argv argv, t_builtin_envp envp)
{
	const size_t	argc = length_strvec(argv);
	int				alert;
	char *const		pwd = _get_pwd(argc, argv, envp, &alert);
	int				result;

	if (!pwd)
		return (EXIT_FAILURE);
	result = EXIT_SUCCESS;
	if ((ft_strlen(pwd) != 0 && chdir(pwd) < 0) || !_setenv(envp, alert))
	{
		if (argc > 1)
			print_err("cd: %s: %s\n", argv[1], strerror(errno));
		else
			print_err("cd: %s\n", strerror(errno));
		result = EXIT_FAILURE;
	}
	free(pwd);
	return (result);
}
