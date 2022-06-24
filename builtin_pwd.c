/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:25 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 21:39:52 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

t_builtin_res	ft_pwd(t_builtin_argv argv, t_builtin_envp envp)
{
	char *const	cwd = getcwd(NULL, 0);

	(void)&argv;
	(void)&envp;
	if (!cwd)
		return (EXIT_FAILURE);
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
