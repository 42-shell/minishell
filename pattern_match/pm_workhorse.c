/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_workhorse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:35:44 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/15 19:28:34 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include "pattern_match_enum.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>	 // malloc

static int	check_dot_dot(char *name, int type)
{
	if (type == DT_DIR)
	{
		if (!(ft_strncmp(name, ".", ft_strlen(name))) \
			|| !(ft_strncmp(name, "..", ft_strlen(name))))
			return (1);
	}
	return (0);
}

static int	create_inter(t_pattern_info *info, char *find, int idx)
{
	char	**temp;

	if (info->malloc_size > info->pm_pos + 1)
		info->pm_interleaving[info->pm_pos] = ft_strdup(find);
	else
	{
		info->malloc_size *= 2;
		temp = (char **)malloc(sizeof(char *) * info->malloc_size);
		if (!temp)
			return (-1);
		temp[info->malloc_size - 1] = NULL;
		idx = 0;
		while (info->pm_interleaving && info->pm_interleaving[idx])
		{
			temp[idx] = ft_strdup(info->pm_interleaving[idx]);
			idx++;
		}
		temp[idx] = ft_strdup(find);
		temp[idx + 1] = NULL;
		if (info->pm_interleaving)
			ft_free_pm(info, RM_PI);
		info->pm_interleaving = temp;
	}
	info->pm_pos += 1;
	return (0);
}

static int	pm_check_pattern(t_pattern_info *info, char *d_name, int d_type)
{
	if (check_dot_dot(d_name, d_type))
		return (0);
	else if (ft_strlen(d_name) < (info->split_text_cnt))
		return (0);
	else if (pm_check_string(info, d_name, d_type))
		return (0);
	return (1);
}

int	pm_workhorse(t_pattern_info *info)
{
	struct dirent	*entity_dir;
	DIR				*current_dir;
	size_t			cnt;

	current_dir = opendir(info->pwd);
	if (!current_dir)
		return (-1);
	entity_dir = readdir(current_dir);
	while (entity_dir)
	{
		if (pm_check_pattern(info, entity_dir->d_name, entity_dir->d_type))
		{
			if (info->pm_flag.r_type == PM_WORD \
											|| info->pm_flag.r_type == PM_SLASH)
				entity_dir->d_name[info->pm_check.cut_pos] = \
														info->pm_check.cut_char;
			if (create_inter(info, entity_dir->d_name, 0))
				return (-1);
		}
		entity_dir = readdir(current_dir);
	}
	return (closedir(current_dir));
}
