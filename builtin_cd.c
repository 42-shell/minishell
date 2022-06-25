/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:25 by jkong             #+#    #+#             */
/*   Updated: 2022/06/25 12:13:16 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "safe_io.h"
#include "libft.h"
#include "string_vector.h"
#include <errno.h>
#include <string.h>

static int	_chdir(size_t argc, char **argv, t_list_var **envp)
{
	char	*str;

	if (argc <= 1 || ft_strcmp(argv[1], "~") == 0)
		str = get_home(*envp);
	else if (ft_strcmp(argv[1], "-") == 0)
		str = get_var(*envp, "OLDPWD", 0);
	else
		str = argv[1];
	return (!(chdir(str) < 0));
}

static int	_setenv(size_t argc, char **argv, t_list_var **envp)
{
	char *const	cwd = getcwd(NULL, 0);

	if (!cwd)
		return (0);
	put_var(envp, "OLDPWD", get_var(*envp, "PWD", 0), VFV_EXPORTED);
	put_var(envp, "PWD", cwd, VFV_EXPORTED);
	if (argc > 1 && ft_strcmp(argv[1], "-") == 0)
		printf("%s\n", cwd);
	free(cwd);
	return (1);
}

t_builtin_res	ft_cd(t_builtin_argv argv, t_builtin_envp envp)
{
	const size_t	argc = length_strvec(argv);

	if (!_chdir(argc, argv, envp) || !_setenv(argc, argv, envp))
	{
		if (argc > 1)
			print_err("cd: %s: %s\n", argv[1], strerror(errno));
		else
			print_err("cd: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
