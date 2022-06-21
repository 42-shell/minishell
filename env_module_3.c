/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:19:03 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 14:58:16 by yongmkim         ###   ########.fr       */
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

	while (env)
	{
		sv = strv_append(NULL, str_dispose(
		str_append(str_append(str_append(NULL, env->id), "="), env->content)));
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
		temp = str_dispose(
		str_append(str_append(str_append(NULL, all_path[i]), "/"), cmd));
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
