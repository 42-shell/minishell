/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:19:03 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 22:33:16 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "libft.h"
#include "string_buffer.h"
#include "minishell.h"
#include "built_in.h"
#include <dirent.h>

int	dirent_print_error(int key)
{
	if (key == FAST_DONE)
	{
		return (print_error("glob", "opendir", \
		"filename cannot be accessed, or cannot malloc enough memory", 1));
	}
	else if (key == ERROR_OCCURED)
		return (print_error("glob", "closedir", "failure", 1));
	return (-1);
}

static void	util_path_finder(char **all_path)
{
	size_t	idx;

	idx = 0;
	while (all_path && all_path[idx])
	{
		free(all_path[idx]);
		idx++;
	}
	free(all_path);
}

static int	is_there_cmd_in_path(char *cmd, char *pwd)
{
	struct dirent	*entity;
	DIR				*dir;

	dir = opendir(pwd);
	if (!dir)
		return (dirent_print_error(FAST_DONE));
	entity = readdir(dir);
	while (entity)
	{
		if (!ft_strcmp(cmd, entity->d_name))
		{
			if (closedir(dir))
				return (dirent_print_error(ERROR_OCCURED));
			return (0);
		}
		entity = readdir(dir);
	}
	if (closedir(dir))
		return (dirent_print_error(ERROR_OCCURED));
	return (-1);
}

char	*path_finder(char *cmd, t_env_list *env)
{
	char		**all_path;
	t_str_buf	*ret_path;
	size_t		idx;

	all_path = ft_split(get_env(env, "PATH"), ':');
	idx = 0;
	ret_path = NULL;
	while (all_path && all_path[idx])
	{
		if (!is_there_cmd_in_path(cmd, all_path[idx]))
		{
			ret_path = str_append(ret_path, all_path[idx]);
			ret_path = str_append(ret_path, "/");
			util_path_finder(all_path);
			return (str_dispose(str_append(ret_path, cmd)));
		}
		idx++;
	}
	util_path_finder(all_path);
	print_error(cmd, NULL, "command not found", 127);
	return (NULL);
}
