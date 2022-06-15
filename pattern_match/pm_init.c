/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:36 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/15 15:44:32 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include "pattern_match_enum.h"
#include <dirent.h>
#include <stdlib.h>

static char	**ft_free_pm(t_pattern_info *info, int key)
{
	size_t	idx;

	idx = 0;
	if (key & RM_PWD)
		free(info->pwd);
	if (key & RM_PM)
	{
		while (info->pattern_split && info->pattern_split[idx])
		{
			free(info->pattern_split[idx]);
			++idx;
		}
		free(info->pattern_split);
	}
	if (key & RM_PI)
	{
		idx = 0;
		while (info->pm_interleaving && info->pm_interleaving[idx])
		{
			free(info->pm_interleaving[idx]);
			++idx;
		}
		free(info->pm_interleaving);
	}
	return (NULL);
}

static void	end_check(char *str, t_pattern_info *info)
{
	if (str[0] == PM_ASTERISK)
		info->pm_flag.l_type = PM_ASTERISK;
	else
		info->pm_flag.l_type = PM_WORD;
	if (str[ft_strlen(str) - 1] == PM_ASTERISK)
		info->pm_flag.r_type = PM_ASTERISK;
	else if (str[ft_strlen(str) - 1] == PM_SLASH)
		info->pm_flag.r_type = PM_SLASH;
	else
		info->pm_flag.r_type = PM_WORD;
	info->malloc_size = 1;
	info->pm_pos = 0;
	info->pm_interleaving = NULL;
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

static int	pm_workhorse(t_pattern_info *info)
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
		if (!check_dot_dot(entity_dir->d_name, entity_dir->d_type) \
			&& ft_strlen(entity_dir->d_name) >= (info->split_text_cnt) \
			&& !check_pattern(info, entity_dir->d_name, entity_dir->d_type))
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

// if return -> NULL -> print "pattern"
char	**ft_pattern_match(char *pattern)
{
	t_pattern_info	info;

	if (!pattern || *pattern == '\0')
		return (NULL);
	info.pwd = ft_get_pwd();
	if (!info.pwd)
		return (NULL);
	end_check(pattern, &info);
	info.pattern_split = ft_split(pattern, PM_ASTERISK);
	if (!info.pattern_split)
		return (ft_free_pm(&info, RM_PWD));
	count_split_size(&info);
	if (pm_workhorse(&info))
		return (ft_free_pm(&info, RM_PWD | RM_PM | RM_PI));
	ft_free_pm(&info, RM_PWD | RM_PM);
	return (info.pm_interleaving);
}
