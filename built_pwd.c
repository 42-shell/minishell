/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:06:56 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 22:40:34 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "safe_io.h"
#include "string_buffer.h"
#include "string_vector.h"
#include <stdlib.h> // free
#include <unistd.h> // getcwd

char	*ft_get_pwd(void)
{
	return (getcwd(NULL, 0));
}

static size_t	pwd_print_error(int key)
{
	if (key == EMPTY_CMD)
		return (print_error("pwd", "parameter", "empty cmd", 1));
	else if (key == ERROR_OCCURED)
		return (print_error("pwd", NULL, "failure", 1));
	return (-1);
}

size_t	ft_pwd(char **argv, t_env_list *env)
{
	char		*buf;
	t_str_buf	*sb;

	(void)env;
	if (!length_strvec(argv))
		return (pwd_print_error(EMPTY_CMD));
	buf = getcwd(NULL, 0);
	if (buf)
	{
		sb = NULL;
		sb = str_append(sb, buf);
		free(buf);
		sb = str_append(sb, "\n");
		buf = str_dispose(sb);
		putstr_safe(buf);
		free(buf);
		return (0);
	}
	else
		return (pwd_print_error(ERROR_OCCURED));
}
