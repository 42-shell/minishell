/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:06:56 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 16:46:09 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "safe_io.h"
#include "string_buffer.h"
#include <stdlib.h>

int	ft_pwd(char **argv, t_env_list **env)
{
	char *const	cwd = getcwd(NULL, 0);
	char		*temp;
	t_str_buf	*sb;

	(void)argv;
	(void)env;
	if (!cwd)
		exit(EXIT_FAILURE);
	sb = str_append(str_append(NULL, cwd), "\n");
	free(cwd);
	temp = str_dispose(sb);
	putstr_safe(temp);
	free(temp);
	return (EXIT_SUCCESS);
}
