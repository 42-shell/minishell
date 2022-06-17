/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:19:03 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/18 02:28:04 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "libft.h"
#include "string_vector.h"
#include <dirent.h>

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
			return (1);
		}
		entity = readdir(dir);
	}
	return (-1);
}

char	*path_finder(char *cmd, t_env_list *env)
{
	char	**all_path;
	char	*find_path;

	all_path = ft_split(get_env(env, "PATH"), ":");
	while (*all_path)
	{
		if (!is_there_cmd_in_path(cmd, *all_path))
		{
			find_path = ft_strdup(*all_path);
			free_strvec(all_path);
			return (find_path);
		}
		all_path++;
	}
	return (NULL);
}
