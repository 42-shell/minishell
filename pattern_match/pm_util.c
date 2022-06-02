/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:15:25 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/02 17:49:21 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include "libft.h"
#include <stdlib.h>

void	count_split_size(t_pattern_info *info)
{
	int	i;
	int cnt;

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
	info.all = 0;
	if (info->split_size == 0)
		info.all = 1;
}

void	ft_check_set(t_pattern_info *info, char *name)
{
	info->pm_check.l_name_pos = 0;
	info->pm_check.r_name_pos = (ft_strlen(name) - 1);
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

void	pm_cmp(t_pattern_info *info, char *name, int unit, int type)
{
	int		idx;
	char	*temp;

	if (info->pm_check.r_pm_pos - info->pm_check.l_pm_pos == 0)
		info->pm_check.return_value = 1;
	else
	{
		if (unit == 1)
		{
			if (type == PM_WORD)
				pm_strcmp_left(info, \
					info->pattern_split[info->pm_check.l_pm_pos], name);
			else if (type == PM_ASTERISK)
				pm_strcmp_plus(info, \
					info->pattern_split[info->pm_check.l_pm_pos], name);
		}
		else if (unit == -1)
		{
			if (type == PM_SLASH)
			{
				idx = info->pm_check.r_pm_pos - 1;
				temp = info->pattern_split[idx];
				temp[ft_strlen(temp) - 1] = '\0';
			}
			if (type == PM_WORD || type == PM_SLASH)
				pm_strcmp_minus(info, \
					info->pattern_split[info->pm_check.r_pm_pos - 1], name);
		}
	}
}
