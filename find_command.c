/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:10:38 by jkong             #+#    #+#             */
/*   Updated: 2022/06/23 15:55:09 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "util_flag.h"
#include "string_buffer.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static char	*_make_path(char *path, char *name)
{
	t_str_buf	*buf;

	buf = NULL;
	if (path)
		buf = str_append_format(buf, "%s/", path);
	buf = str_append(buf, name);
	return (str_dispose(buf));
}

static int	_file_status(char *path)
{
	struct stat		st;

	if (stat(path, &st) < 0)
		return (1);
	if (S_ISDIR(st.st_mode))
		return (2);
	return (0);
}

char	*find_command(t_shell *sh, char *name)
{
	char	*var;
	char	*path_list;
	char	*next_path;
	char	*full_path;

	if (ft_strchr(name, '/'))
		return (_make_path(NULL, name));
	full_path = NULL;
	var = get_var(sh->var_list, "PATH", 1);
	path_list = var;
	while (path_list)
	{
		next_path = ft_strchr(path_list, ':');
		if (next_path)
			*next_path++ = '\0';
		full_path = _make_path(path_list, name);
		if (_file_status(full_path) == 0)
			break ;
		free(full_path);
		path_list = next_path;
	}
	free(var);
	return (full_path);
}
