/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_check_pattern.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:15:25 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/15 20:52:20 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pm.h"
#include "libft.h"
#include <dirent.h> //DT macro

static void	init_check_info(t_pattern_info *info, char *name)
{
	info->pm_check.l_name_pos = 0;
	info->pm_check.l_pm_pos = 0;
	info->pm_check.r_pm_pos = (info->split_size);
	info->pm_check.return_value = 0;
	info->pm_check.cut_pos = 0;
	info->pm_check.cut_char = name[0];
}

static void	pm_cmp_middle(t_pattern_info *info, char *name, \
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

static int	is_edge_str_equal(t_pattern_info *info, char *name, \
														int l_to_r, size_t idx)
{
	char	*temp;
	size_t	temp_len;

	temp = info->pattern_split[idx];
	temp_len = ft_strlen(temp);
	if (l_to_r == 1)
	{
		if (temp_len == 0)
			return (0);
		return (!ft_strncmp(name, temp, temp_len));
	}
	else
	{
		return (!ft_strncmp(&name[ft_strlen(name) - temp_len], temp, temp_len));
	}
}

static void	pm_cmp_edge(t_pattern_info *info, char *name, int l_to_r, size_t idx)
{
	size_t	pos;

	if (info->pm_check.r_pm_pos >= info->pm_check.l_pm_pos)
	{
		if (is_edge_str_equal(info, name, l_to_r, idx))
		{
			if (l_to_r == 1)
			{
				info->pm_check.l_pm_pos++;
				info->pm_check.l_name_pos = ft_strlen(info->pattern_split[idx]);
			}
			else
			{
				if (info->pm_check.r_pm_pos != info->pm_check.l_pm_pos)
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

int	pm_check_string(t_pattern_info *info, char *name, int file_type)
{
	char	*temp;

	if (info->pm_flag.r_type == PM_SLASH && file_type != DT_DIR)
		return (1);
	init_check_info(info, name);
	if (info->pm_flag.r_type == PM_SLASH)
	{
		temp = info->pattern_split[info->pm_check.r_pm_pos - 1];
		temp[ft_strlen(temp) - 1] = '\0';
	}
	if (info->pm_flag.l_type == PM_WORD)
		pm_cmp_edge(info, name, 1, 0);
	if (info->pm_check.r_pm_pos < info->pm_check.l_pm_pos)
		return (info->pm_check.r_pm_pos - info->pm_check.l_pm_pos);
	if ((info->pm_flag.r_type == PM_WORD || info->pm_flag.r_type == PM_SLASH))
		pm_cmp_edge(info, name, -1, info->pm_check.r_pm_pos - 1);
	if (info->pm_check.r_pm_pos < info->pm_check.l_pm_pos)
		return (info->pm_check.r_pm_pos - info->pm_check.l_pm_pos);
	while (info->pm_check.r_pm_pos > info->pm_check.l_pm_pos)
		pm_cmp_middle(info, name, info->pm_check.l_pm_pos, \
											info->pm_check.l_name_pos);
	return (info->pm_check.r_pm_pos - info->pm_check.l_pm_pos);
}
