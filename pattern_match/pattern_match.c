/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:36 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/01 22:27:37 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include "built_in.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>

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
}

static int	create_inter(t_pattern_info *info, char *find)
{
	char	**temp;
	int		idx;

	if (info->malloc_size > info->pm_cnt + 1)
		info->pm_interleaving[info->pm_cnt + 1] = ft_strdup(find);
	else
	{
		info->malloc_size *= 2;
		temp = (char **)malloc(sizeof(char *) * info->malloc_size);
		if (!temp)
			return (-1);
		temp[info->malloc_size - 1] = NULL;
		idx = -1;
		while (info->pm_interleaving[++idx])
			temp[idx] = ft_strdup(info->pm_interleaving[idx]);
		temp[idx] = ft_strdup(find);
		temp[idx + 1] = NULL;
		if (info->pm_interleaving)
			ft_free_pm(info, 2);
		info->pm_interleaving = temp;
	}
	info->pm_cnt += 1;
	return (0);
}

static int	check_pattern(t_pattern_info *info, char *name, int file_type)
{
	if (info->all & 1)
		return (1);
	if (info->pm_flag.r_type == PM_SLASH && file_type != 4)
		return (0);
	ft_check_set(info, name);
	if (info->pm_flag.l_type == PM_WORD)
	{
		pm_strcmp(info, 1, 0);
		if (info->pm_flag.r_type == PM_WORD)
			pm_strcmp(info, -1, 0);
		if (info->pm_flag.r_type == PM_SLASH)
			pm_strcmp(info, -1, PM_SLASH);
		while (info->pm_check.r_pm_pos - info->pm_check.l_pm_pos > 0)
			pm_strcmp(info, 1, PM_ASTERISK);
	}
	else if (info->pm_flag.l_type == PM_ASTERISK)
	{
		if (info->pm_flag.r_type == PM_WORD)
			pm_strcmp(info, -1, 0);
		if (info->pm_flag.r_type == PM_SLASH)
			pm_strcmp(info, -1, PM_SLASH);
		while (info->pm_check.r_pm_pos - info->pm_check.l_pm_pos > 0)
			pm_strcmp(info, 1, PM_ASTERISK);
	}
	return (info->pm_check.return_value);
}

static int	pm_workhorse(t_pattern_info *info)
{
	struct dirent	*entity_dir;
	DIR				*current_dir;
	int				cnt;

	current_dir = opendir(info->pwd);
	if (!current_dir)
		return (-1);
	entity_dir = readdir(current_dir);
	while (entity_dir)
	{
		if (check_pattern(info, entity_dir->d_name, entity_dir->d_type))
		{
			if (create_inter(info, entity_dir->d_name))
				return (-1);
		}
		entity_dir = readdir(current_dir);
	}
	closedir(current_dir);
}

char	**ft_pattern_match(char *pattern)
{
	t_pattern_match	info;

	if (!pattern || *pattern == '\0')
		return (NULL);
	info.pwd = get_pwd();
	if (!info.pwd)
		return (NULL);
	end_check(pattern, &info);
	info.pattern_split = ft_split(pattern, PM_ASTERISK);
	if (!info.pattern_split)
		return (NULL);
	count_split_size(info);
	info.malloc_size = 1;
	info.pm_cnt = 0;
	info.pm_interleaving = NULL;
	if (pm_workhorse(&info))
		return (ft_free_pm(&info, 1 + 2));
	ft_free_pm(&info, 1);
	return (info.pm_interleaving);
}
