/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:19:03 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 13:44:20 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "libft.h"
#include "string_buffer.h"
#include "string_vector.h"
#include "minishell.h"
#include "built_in.h"
#include <dirent.h>
#include <sys/stat.h>

char	**env_to_strvec(t_env_list *env)
{
	t_str_vec	*sv;
	t_str_buf	*sb;

	sv = NULL;
	while (env)
	{
		sb = NULL;
		sb = str_append(sb, env->id);
		sb = str_append(sb, "=");
		sb = str_append(sb, env->content);
		sv = strv_append(sv, str_dispose(sb));
		env = env->next;
	}
	return (strv_dispose(sv));
}

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

/*
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
*/

/*
char	*path_finder(char *cmd, t_env_list *env)
{
	char		**all_path;
	t_str_buf	*ret_path;
	size_t		idx;

	all_path = ft_split(get_env(env, "PATH"), ':');
	idx = 0;
	ret_path = NULL;
	errno = 0;
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
*/

//return (print_error(cmd, NULL, "permission denied", 126));
static int	check_path_stat(char *cmd, int key)
{
	struct stat	stat_info;

	if (stat(cmd, &stat_info) < 0)
	{
		if (key == ON_VISIBLE)
			return (print_error(cmd, NULL, "command not found", EX_NOTFOUND));
		else
			return (EX_NOTFOUND);
	}
	if (stat_info.st_mode & S_IFDIR)
	{
		if (key == ON_VISIBLE)
			return (print_error(cmd, NULL, "is a directory", EX_NOEXEC));
		return (EX_NOEXEC);
	}
	return (0);
}

static char	*check_path_abs(char *path)
{
	if (check_path_stat(path, ON_VISIBLE))
		return (NULL);
	else
		return (path);
}

char	*path_finder(char *cmd, t_env_list *env)
{
	char		**all_path;
	char		*temp;
	char		*result;
	size_t		i;

	if (cmd && cmd[0] == '/')
		return (check_path_abs(cmd));
	all_path = ft_split(get_env(env, "PATH"), ':');
	errno = 0;
	i = 0;
	result = NULL;
	while (all_path[i])
	{
		temp = str_dispose(str_append(str_append(str_append(NULL, all_path[i]), "/"), cmd));
		if (!check_path_stat(temp, NON_VISIBLE))
		{
			result = temp;
			break ;
		}
		free(temp);
		i++;
	}
	free_strvec(all_path);
	return (result);
}
