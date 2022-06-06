/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_work.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:15:25 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/06 18:00:58 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"

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
												size_t pm_pos, size_t na_pos)
{
	size_t	size;
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

#include <stdio.h>
static int	pm_cmp_abs_work(t_pattern_info *info, char *name, \
														int unit, size_t idx)
{
	char	*temp;
	size_t	temp_len;

	temp = info->pattern_split[idx];
	temp_len = ft_strlen(temp);
	if (temp_len == 0)
		temp_len = 1;
	if (unit == 1)
	{
		printf("l - %s , %zu\n", name, ft_strlen(temp));
		return (!ft_strncmp(name, temp, temp_len));
	}
	else
	{
		printf("r - %s , %zu\n", &name[ft_strlen(name) - temp_len], temp_len);
		return (!ft_strncmp(&name[ft_strlen(name) - temp_len], temp, temp_len));
	}
}

static void	pm_cmp_abs(t_pattern_info *info, char *name, int unit, size_t idx)
{
	size_t	pos;

	if (info->pm_check.r_pm_pos > info->pm_check.l_pm_pos)
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
	while (info->pm_check.r_pm_pos > info->pm_check.l_pm_pos)
		pm_cmp_strstr(info, name, info->pm_check.l_pm_pos, \
											info->pm_check.l_name_pos);
	return (info->pm_check.r_pm_pos - info->pm_check.l_pm_pos);
}
