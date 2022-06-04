/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:36 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/04 15:45:53 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
//#include "built_in.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

// need delete this function
char	*ft_get_pwd(void)
{
	char *buf;

	buf = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
	if (!buf)
		return (NULL);
	if (getcwd(buf, PATH_MAX))
		return (buf);
	else
		return (NULL);
}
// need delete this function
// /////////////////////////////////////////////////////

static char	**ft_free_pm(t_pattern_info *info, int key)
{
	int	idx;

	idx = 0;
	if (key & 1)
	{
		while (info->pattern_split && info->pattern_split[idx])
		{
			free(info->pattern_split[idx]);
			++idx;
		}
		free(info->pattern_split);
		free(info->pwd);
	}
	if (key & 2)
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
			ft_free_pm(info, 2);
		info->pm_interleaving = temp;
	}
	info->pm_pos += 1;
	return (0);
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
		if (!check_dot_dot(entity_dir->d_name, entity_dir->d_type) && \
			ft_strlen(entity_dir->d_name) >= (info->split_text_cnt))
		{
			if (!check_pattern(info, entity_dir->d_name, entity_dir->d_type))
			{
				if(info->pm_flag.r_type == PM_WORD \
					|| info->pm_flag.r_type == PM_SLASH)
					entity_dir->d_name[info->pm_check.cut_pos] = \
													info->pm_check.cut_char;
				if (create_inter(info, entity_dir->d_name, 0))
					return (-1);
			}
		}
		entity_dir = readdir(current_dir);
	}
	closedir(current_dir);
	return (0);
}

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
		return (NULL);
	count_split_size(&info);
	info.malloc_size = 1;
	info.pm_pos = 0;
	info.pm_interleaving = NULL;
	if (pm_workhorse(&info))
		return (ft_free_pm(&info, 1 + 2));
	ft_free_pm(&info, 1);
	return (info.pm_interleaving);
}
