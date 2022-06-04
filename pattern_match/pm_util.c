/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:15:25 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/04 11:38:27 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include "libft.h"
#include <stdlib.h>

void	count_split_size(t_pattern_info *info)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (info->pattern_split[i])
	{
		cnt += ft_strlen(info->pattern_split[i]);
		++i;
	}
	info->split_size = i;
	info->split_text_cnt = cnt;
	if (info->pm_flag.r_type == PM_SLASH && info->split_text_cnt != 1)
		info->split_text_cnt -= 1;
	info->all = 0;
	if (info->split_size == 0)
		info->all = 1;
}

void	ft_check_set(t_pattern_info *info, char *name)
{
	info->pm_check.l_name_pos = 0;
	info->pm_check.l_pm_pos = 0;
	info->pm_check.r_pm_pos = (info->split_size);
	info->pm_check.return_value = 0;
}

char	**ft_free_pm(t_pattern_info *info, int key)
{
	int	idx;

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

void	pm_cmp_abs(t_pattern_info *info, char *name, int unit, int idx)
{
	int	pos;

	if (info->pm_check.r_pm_pos - info->pm_check.l_pm_pos > 0)
	{
		if (pm_cmp_abs_work(info, name, unit, idx))
		{
			if (unit == 1)
			{
				info->pm_check.l_pm_pos += idx;
				info->pm_check.l_name_pos = ft_strlen(info->pattern_split[idx]);
			}
			else
			{
				info->pm_check.r_pm_pos += idx;
				pos = ft_strlen(name) - ft_strlen(info->pattern_split[idx]);
				name[pos] = '\0';
			}
		}
		else
			info->pm_check.l_pm_pos = info->pm_check.r_pm_pos + 1;
	}
}
