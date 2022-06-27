/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:10:38 by jkong             #+#    #+#             */
/*   Updated: 2022/06/27 21:33:31 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "util_flag.h"
#include "string_buffer.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char	*resolve_path(char *path, char *name)
{
	t_str_buf	*buf;

	buf = NULL;
	if (path)
		buf = str_append_format(buf, "%s/", path);
	buf = str_append(buf, name);
	return (str_dispose(buf));
}

t_file_status	file_status(char *path)
{
	struct stat	st;

	if (stat(path, &st) < 0)
		return (FS_NOT_FOUND);
	if (S_ISDIR(st.st_mode))
		return (2);
	else
		return (1);
}

int	is_absolute_path(char *name, t_file_status type)
{
	if (type == FS_PROGRAM)
		return (!!ft_strchr(name, '/'));
	else if (type == FS_PATHNAME)
	{
		if (ft_strlen(name) != 0)
		{
			if (name[0] == '/')
				return (1);
			if (name[0] == '.' && (name[1] == '/' || name[1] == '\0'))
				return (1);
			if (name[0] == '.'
				&& name[1] == '.' && (name[2] == '/' || name[2] == '\0'))
				return (1);
		}
		return (0);
	}
	else
	{
		print_err("Unsupported path type %d\n", type);
		exit(EXIT_FAILURE);
	}
}

char	*find_path(char *var, char *name, t_file_status type)
{
	char	*new_var;
	char	*path_list;
	char	*next_path;
	char	*full_path;

	full_path = NULL;
	if (var)
		new_var = str_dispose(str_append(NULL, var));
	else
		new_var = NULL;
	path_list = new_var;
	while (path_list)
	{
		next_path = ft_strchr(path_list, ':');
		if (next_path)
			*next_path++ = '\0';
		full_path = resolve_path(path_list, name);
		if (file_status(full_path) == type)
			break ;
		free(full_path);
		full_path = NULL;
		path_list = next_path;
	}
	free(new_var);
	return (full_path);
}
