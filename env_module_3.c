/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:19:03 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 16:42:07 by jkong            ###   ########.fr       */
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
		sv = strv_append(sv, str_dispose(str_append(str_append(str_append(
								NULL, env->id), "="), env->content)));
		env = env->next;
	}
	return (strv_dispose(sv));
}

//permission denied
//command not found
//is a directory
static int	check_path_stat(char *cmd)
{
	struct stat	stat_info;

	if (stat(cmd, &stat_info) < 0)
		return (EX_NOTFOUND);
	if (stat_info.st_mode & S_IFDIR)
		return (EX_NOEXEC);
	return (EXIT_SUCCESS);
}

static char	*check_path_abs(char *path)
{
	if (check_path_stat(path) == EXIT_SUCCESS)
		return (path);
	return (NULL);
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
		temp = str_dispose(str_append(str_append(str_append(
							NULL, all_path[i]), "/"), cmd));
		if (check_path_stat(temp) == EXIT_SUCCESS)
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
