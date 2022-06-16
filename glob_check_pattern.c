/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_check_pattern.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:15:25 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/16 16:27:47 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"
#include <dirent.h> //DT macro

static void	init_check_info(t_glob_info *info, char *name)
{
	info->pattern_check.l_name_pos = 0;
	info->pattern_check.l_pattern_pos = 0;
	info->pattern_check.r_pattern_pos = (info->split_size);
	info->pattern_check.return_value = 0;
	info->pattern_check.cut_pos = 0;
	info->pattern_check.cut_char = name[0];
}

static void	pm_cmp_middle(t_glob_info *info, char *name, \
												size_t pm_pos, size_t na_pos)
{
	size_t	size;
	char	*pos;

	size = ft_strlen(&name[na_pos]);
	pos = ft_strnstr(&name[na_pos], info->pattern_split[pm_pos], size);
	if (pos)
	{
		info->pattern_check.l_pattern_pos += 1;
		info->pattern_check.l_name_pos += (pos - &name[na_pos] + 1);
	}
	else
	{
		info->pattern_check.l_pattern_pos = \
										info->pattern_check.r_pattern_pos + 1;
	}
}

static int	is_edge_str_equal(t_glob_info *info, char *name, \
														int l_or_r, size_t idx)
{
	char	*temp;
	size_t	temp_len;

	temp = info->pattern_split[idx];
	temp_len = ft_strlen(temp);
	if (l_or_r == 1)
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

static void	pm_cmp_edge(t_glob_info *info, char *name, int l_or_r, size_t idx)
{
	size_t	pos;

	if (info->pattern_check.r_pattern_pos >= info->pattern_check.l_pattern_pos)
	{
		if (is_edge_str_equal(info, name, l_or_r, idx))
		{
			if (l_or_r == 1)
			{
				info->pattern_check.l_pattern_pos++;
				info->pattern_check.l_name_pos = \
											ft_strlen(info->pattern_split[idx]);
			}
			else
			{
				if (info->pattern_check.r_pattern_pos != \
											info->pattern_check.l_pattern_pos)
					info->pattern_check.r_pattern_pos--;
				pos = ft_strlen(name) - ft_strlen(info->pattern_split[idx]);
				info->pattern_check.cut_char = name[pos];
				info->pattern_check.cut_pos = pos;
				name[pos] = '\0';
			}
		}
		else
			info->pattern_check.l_pattern_pos = \
										info->pattern_check.r_pattern_pos + 1;
	}
}

int	pattern_check.string(t_pattern_info *info, char *name, int file_type)
{
	char	*temp;

	if (info->glob_flag.r_type == PM_SLASH && file_type != DT_DIR)
		return (1);
	init_check_info(info, name);
	if (info->glob_flag.r_type == PM_SLASH)
	{
		temp = info->pattern_split[info->pattern_check.r_pattern_pos - 1];
		temp[ft_strlen(temp) - 1] = '\0';
	}
	if (info->glob_flag.l_type == PM_WORD)
		pm_cmp_edge(info, name, LHS, 0);
	if (info->pattern_check.r_pattern_pos < info->pattern_check.l_pattern_pos)
		return (info->pattern_check.r_pattern_pos \
										- info->pattern_check.l_pattern_pos);
	if ((info->glob_flag.r_type == PM_WORD \
										|| info->glob_flag.r_type == PM_SLASH))
		pm_cmp_edge(info, name, RHS, info->pattern_check.r_pattern_pos - 1);
	if (info->pattern_check.r_pattern_pos < info->pattern_check.l_pattern_pos)
		return (info->pattern_check.r_pattern_pos \
										- info->pattern_check.l_pattern_pos);
	while (info->pattern_check.r_pattern_pos \
											> info->pattern_check.l_pattern_pos)
		pm_cmp_middle(info, name, info->pattern_check.l_pattern_pos, \
												info->pattern_check.l_name_pos);
	return (info->pattern_check.r_pattern_pos \
										- info->pattern_check.l_pattern_pos);
}
