/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_workhorse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:35:44 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 16:39:29 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"
#include "string_vector.h"
#include "string_buffer.h"
#include "minishell.h"
#include <dirent.h>	// DT macro
#include <stdlib.h>	 // free

t_str_vec	*ft_free_pm(t_glob_info *info, int key)
{
	size_t	idx;

	if (key & RM_PATTERN_SPLIT)
	{
		idx = 0;
		while (info->pattern_split && info->pattern_split[idx])
		{
			free(info->pattern_split[idx]);
			idx++;
		}
		free(info->pattern_split);
	}
	if (key & RM_STR_VEC)
		free_strvec(info->glob_matched->arr);
	return (NULL);
}

static int	check_dot_dot(char *name, int type)
{
	if (type == DT_DIR)
	{
		if (!(ft_strcmp(name, ".")) || !(ft_strcmp(name, "..")))
			return (1);
	}
	return (0);
}

static int	check_pattern(t_glob_info *info, char *d_name, int d_type)
{
	if (check_dot_dot(d_name, d_type))
		return (0);
	else if (ft_strlen(d_name) < (info->split_text_cnt))
		return (0);
	else if (check_string(info, d_name, d_type))
		return (0);
	return (1);
}

// add sort
static void	glob_append(t_glob_info *info, char *name, int type)
{
	t_str_buf	*sb;

	sb = NULL;
	sb = str_append(sb, name);
	if (info->glob_flag.r_type == GLOB_SLASH && type == DT_DIR)
		sb = str_append(sb, "/");
	info->glob_matched = strv_append(info->glob_matched, str_dispose(sb));
}

int	glob_workhorse(t_glob_info *info)
{
	struct dirent	*entity_dir;
	DIR				*current_dir;

	current_dir = opendir(info->pwd);
	if (!current_dir)
		exit(EXIT_FAILURE); //???
	entity_dir = readdir(current_dir);
	while (entity_dir)
	{
		if (check_pattern(info, entity_dir->d_name, entity_dir->d_type))
		{
			if (info->glob_flag.r_type == GLOB_WORD \
			|| info->glob_flag.r_type == GLOB_SLASH)
				entity_dir->d_name[info->check_info.cut_pos] \
				= info->check_info.cut_char;
			glob_append(info, entity_dir->d_name, entity_dir->d_type);
		}
		entity_dir = readdir(current_dir);
	}
	closedir(current_dir);
	return (0);
}
