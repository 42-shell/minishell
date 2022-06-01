/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:36 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/01 10:48:41 by yongmkim         ###   ########.fr       */
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

static char **ft_free_pm(t_pattern_info *info, int key)
{
	int idx;

	idx = 0;
	if (key & 1)
	{
		while (info->pattern_split[idx])
		{
			free(info->pattern_split[idx]);
			++idx;
		}
		free(info->pattern_split);
	}
	if (key & 2)
	{
		idx = 0;
		while (info->pm_interleaving[idx])
		{
			free(info->pm_interleaving[idx]);
			++idx;
		}
		free(info->pm_interleaving);
	}
	return (NULL);
}
static int check_pattern(t_pattern_info *info, char *name, int file_type)
{
	if (info->pm_flag.l_type == PM_WORD)
		// check left_strcmp
	if (info->pm_flag.r_type == PM_WORD)
		// check right_strcmp
	if (info->pm_flag.l_type == PM_ASTERISK)
		//check strcmp_mov

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
	closedir(currend_dir);
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
	info.malloc_size = 1;
	info.pm_cnt = 0;
	info.pm_interleaving = NULL;
	if (pm_workhorse(&info))
		return (ft_free_pm(&info, 1 + 2));
	ft_free_pm(&info, 1);
	return (info.pm_interleaving);
}
