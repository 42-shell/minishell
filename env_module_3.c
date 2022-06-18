/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:19:03 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/19 02:53:28 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "libft.h"
#include "string_buffer.h"
#include "safe_io.h"
#include "minishell.h"
#include <dirent.h>

char	*path_finder(char *cmd, t_env_list *env);
void	print_env(t_env_list *head, int key);

static void	str_manage(t_str_buf *sb)
{
	char	*str;

	str = str_dispose(sb);
	putstr_safe(str);
	free(str);
}

//quote = key && (!head->content.visible || !head->content.content);
void	print_env(t_env_list *head, int key)
{
	t_str_buf	*sb;

	sb = NULL;
	while (head)
	{
		if ((head->content.visible != HIDE_VISIBLE) \
		&& (key || head->content.visible))
		{
			if (key)
				sb = str_append(sb, "declare -x ");
			sb = str_append(sb, head->content.id);
			if (head->content.visible)
			{
				sb = str_append(sb, "=");
				if (key)
					sb = str_append(sb, "\"");
				sb = str_append(sb, head->content.content);
				if (key)
					sb = str_append(sb, "\"");
			}
			sb = str_append(sb, "\n");
		}
		head = head->next;
	}
	str_manage(sb);
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

static int	is_there_cmd_in_path(char *cmd, char *pwd, t_env_list *env)
{
	struct dirent	*entity;
	DIR				*dir;

	dir = opendir(pwd);
	if (!dir)
		return (print_error("glob", "opendir", \
			"filename cannot be accessed, or cannot malloc enough memory"));
	entity = readdir(dir);
	while (entity)
	{
		if (!ft_strcmp(cmd, entity->d_name))
		{
			if (closedir(dir))
				return (print_error("glob", "closedir", "failure"));
			return (0);
		}
		entity = readdir(dir);
	}
	if (closedir(dir))
		return (print_error("glob", "closedir", "failure"));
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
		if (!is_there_cmd_in_path(cmd, all_path[idx], env))
		{
			ret_path = str_append(ret_path, all_path[idx]);
			ret_path = str_append(ret_path, "/");
			util_path_finder(all_path);
			return (str_dispose(str_append(ret_path, cmd)));
		}
		idx++;
	}
	util_path_finder(all_path);
	change_env(env, "EXIT_STATUS", "127");
	print_error(cmd, NULL, "command not found");
	return (NULL);
}
