/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:19:03 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/18 02:52:58 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "libft.h"
#include "string_buffer.h"
#include <dirent.h>

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
		return (-1);
	entity = readdir(dir);
	while (entity)
	{
		if (!ft_strcmp(cmd, entity->d_name))
		{
			closedir(dir);
			return (0);
		}
		entity = readdir(dir);
	}
	closedir(dir);
	return (-1);
}

char	*path_finder(char *cmd, t_env_list *env)
{
	char		**all_path;
	t_str_buf	*ret_path;
	size_t		idx;

	all_path = ft_split(get_env(env, "PATH"), ':');
	while (all_path[idx])
	{
		if (!is_there_cmd_in_path(cmd, all_path[idx]))
		{
			ret_path = str_append(ret_path, all_path[idx]);
			util_path_finder(all_path);
			return (str_dispose(str_append(ret_path, cmd)));
		}
		idx++;
	}
	util_path_finder(all_path);
	return (NULL);
}
