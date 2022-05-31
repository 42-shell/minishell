/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:36 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:11 by yongmkim         ###   ########.fr       */
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
	return (NULL);
}
static int inter_pattern(t_pattern_info *info, char *name, int file_type)
{

}

static int	pm_workhorse(t_pattern_info *info)
{
	DIR				*current_dir;
	struct dirent	*entity_dir;
	int				cnt;
	
	current_dir = opendir(info->pwd);
	if (!current_dir)
		return (-1);
	entity_dir = readdir(current_dir);
	while (entity_dir)
	{
		if (inter_pattern(info, entity_dir->d_name, entity_dir->d_type))
		{
			// add to interleaving 
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
	info.malloc_size = 4;
	if (pm_workhorse(&info))
		return (ft_free_pm(&info, 1);
	
	// 1. find pm (check pm_idx)
	// 2. malloc ** interleaving
	// 3. check mark_pm, ft_strdup target string to interleaving
	// 4. free pattern_split
}
