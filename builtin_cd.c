/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:25 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 11:08:16 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "safe_io.h"
#include "libft.h"
#include "string_vector.h"

static int	_chdir(size_t argc, char **argv, t_list_var **envp)
{
	char	*str;

	if (argc < 1)
		return (0);
	else if (argc > 1)
		str = argv[1];
	else
		str = "~";
	if (ft_strcmp(str, "~") == 0)
		return (!(chdir(get_var(*envp, "HOME", 0)) < 0));
	else if (ft_strcmp(str, "-") == 0)
		return (!(chdir(get_var(*envp, "OLDPWD", 0)) < 0));
	return (!(chdir(str) < 0));
}

static void	_setenv(size_t argc, char **argv, t_list_var **envp)
{
	char *const	cwd = getcwd(NULL, 0);

	if (!cwd)
		exit(EXIT_FAILURE);
	put_var(envp, "OLDPWD", get_var(*envp, "PWD", 0), VFV_EXPORTED);
	put_var(envp, "PWD", cwd, VFV_EXPORTED);
	if (argc > 1 && ft_strcmp(argv[1], "-") == 0)
		printf("%s\n", cwd);
	free(cwd);
}

t_builtin_res	ft_cd(t_builtin_argv argv, t_builtin_envp envp)
{
	const size_t	argc = length_strvec(argv);

	if (!_chdir(argc, argv, envp))
	{
		puterr_safe("cd: chdir\n");
		return (EXIT_FAILURE);
	}
	_setenv(argc, argv, envp);
	return (EXIT_SUCCESS);
}
