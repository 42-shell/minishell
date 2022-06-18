/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:06:56 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/19 03:24:07 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"
#include "safe_io.h"
#include <stdlib.h> // free
#include <unistd.h> // getcwd

char	*ft_get_pwd(void)
{
	return (getcwd(NULL, 0));
}

static size_t	pwd_print_error(int key, t_env_list *env)
{
	change_env(env, "EXIT_STATUS", "1");
	if (key == EMPTY_CMD)
		return (print_error("pwd", "parameter", "empty cmd"));
	else if (key == ERROR_OCCURED)
		return (print_error("pwd", "getcwd", "failure"));
	return (-1);
}

size_t	ft_pwd(char **argv, t_env_list *env)
{
	char	*buf;

	change_late_cmd(env, "pwd", BUILT_IN);
	if (!ft_getarr_size(argv))
		return (pwd_print_error(EMPTY_CMD, env));
	buf = getcwd(NULL, 0);
	if (buf)
	{
		putstr_safe(buf);
		putstr_safe("\n");
		free(buf);
		change_env(env, "EXIT_STATUS", "0");
		return (0);
	}
	else
		return (pwd_print_error(ERROR_OCCURED, env));
}
