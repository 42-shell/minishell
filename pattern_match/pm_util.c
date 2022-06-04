/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:15:25 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/04 16:27:57 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include "libft.h"
#include <stdlib.h>

static void	ft_check_set(t_pattern_info *info, char *name)
{
	info->pm_check.l_name_pos = 0;
	info->pm_check.l_pm_pos = 0;
	info->pm_check.r_pm_pos = (info->split_size);
	info->pm_check.return_value = 0;
	info->pm_check.cut_pos = 0;
	info->pm_check.cut_char = name[0];
}

static void	pm_cmp_strstr(t_pattern_info *info, char *name, \
														int pm_pos, int na_pos)
{
	int		size;
	char	*pos;

	size = ft_strlen(&name[na_pos]);
	pos = ft_strnstr(&name[na_pos], info->pattern_split[pm_pos], size);
	if (pos)
	{
		info->pm_check.l_pm_pos += 1;
		info->pm_check.l_name_pos += (pos - &name[na_pos] + 1);
	}
	else
	{
		info->pm_check.l_pm_pos = info->pm_check.r_pm_pos + 1;
	}
}

static int	pm_cmp_abs_work(t_pattern_info *info, char *name, int unit, int idx)
{
	char	*temp;

	temp = info->pattern_split[idx];
	if (unit == 1)
	{
		return (!ft_strncmp(name, temp, ft_strlen(temp)));
	}
	else
	{
		return (!ft_strncmp(&name[ft_strlen(name) - ft_strlen(temp)], temp, \
			ft_strlen(temp)));
	}
}

static void	pm_cmp_abs(t_pattern_info *info, char *name, int unit, int idx)
{
	int	pos;

	if (info->pm_check.r_pm_pos - info->pm_check.l_pm_pos > 0)
	{
		if (pm_cmp_abs_work(info, name, unit, idx))
		{
			if (unit == 1)
			{
				info->pm_check.l_pm_pos++;
				info->pm_check.l_name_pos = ft_strlen(info->pattern_split[idx]);
			}
			else
			{
				info->pm_check.r_pm_pos--;
				pos = ft_strlen(name) - ft_strlen(info->pattern_split[idx]);
				info->pm_check.cut_char = name[pos];
				info->pm_check.cut_pos = pos;
				name[pos] = '\0';
			}
		}
		else
			info->pm_check.l_pm_pos = info->pm_check.r_pm_pos + 1;
	}
}

int	check_pattern(t_pattern_info *info, char *name, int file_type)
{
	char	*temp;

	if (info->all & 1)
		return (0);
	if (info->pm_flag.r_type == PM_SLASH && file_type != PM_DIRECTORY)
		return (1);
	ft_check_set(info, name);
	if (info->pm_flag.r_type == PM_SLASH)
	{
		temp = info->pattern_split[info->pm_check.r_pm_pos - 1];
		temp[ft_strlen(temp) - 1] = '\0';
	}
	if (info->pm_flag.l_type == PM_WORD)
		pm_cmp_abs(info, name, 1, 0);
	if ((info->pm_flag.r_type == PM_WORD || info->pm_flag.r_type == PM_SLASH))
		pm_cmp_abs(info, name, -1, info->pm_check.r_pm_pos - 1);
	while (info->pm_check.r_pm_pos - info->pm_check.l_pm_pos > 0)
		pm_cmp_strstr(info, name, info->pm_check.l_pm_pos, \
											info->pm_check.l_name_pos);
	return (info->pm_check.r_pm_pos - info->pm_check.l_pm_pos);
}
