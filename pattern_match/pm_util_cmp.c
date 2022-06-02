/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_util_cmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:35:44 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/02 19:37:43 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include "libft.h"

// if not match -> return_value = 0 and set l_pm_pos > r_pm_pos
// 증가하면서 strcmp 하고, l_name_pos, l_pm_pos 움직이기
// 다르면 l_pm_pos  r_pm_pos보다 크게 셋
//	if (name[idx] != info->pattern_split[info->pm_check.l_pm_pos][idx])
//
//	l_name_pos
//	l_pm_pos
//
//

void	pm_strcmp_plus(t_pattern_info *info, char *s1, char *s2)
{
	int	idx;
	int	jdx;
	int	org;
	int	check;

	idx = 0;
	jdx = 0;
	org = 0;
	check = 0;
	while (s1[idx])
	{
		if (s1[idx] == s2[info->pm_check.l_name_pos + jdx])
		{
			check = 1;
			++idx;
		}
		else
		{
			++org;
			jdx = org;
			idx = 0;
			check = 0;
		}
		++jdx;
	}
	if (check & 1)
	{
		info->pm_check.l_name_pos += idx;
		info->pm_check.l_pm_pos += 1;
		info->pm_check.return_value = 1;
	}
	else
	{
		info->pm_check.l_pm_pos = info->pm_check.r_pm_pos;
		info->pm_check.return_value = 0;
	}

}

void	pm_strcmp_left(t_pattern_info *info, char *s1, char *s2)
{
	int	idx;
	int	diff;

	idx = 0;
	diff = 0;
	while (s1[idx])
	{
		if (s1[idx]!= s2[info->pm_check.l_name_pos + idx])
		{
			info->pm_check.l_pm_pos = info->pm_check.r_pm_pos;
			info->pm_check.return_value = 0;
			++diff;
		}
		++idx;
	}
	if (diff == 0)
	{
		info->pm_check.l_name_pos += idx;
		info->pm_check.l_pm_pos += 1;
		info->pm_check.return_value = 1;
	}
}

void	pm_strcmp_minus(t_pattern_info *info, char *s1, char *s2)
{
	int	idx;
	int	r_idx;
	int	diff;

	idx = 0;
	r_idx = ft_strlen(s2) - ft_strlen(s1);
	diff = 0;
	while (s1[idx])
	{
		if (s1[idx] != s2[r_idx + idx])
		{
			info->pm_check.l_pm_pos = info->pm_check.r_pm_pos;
			info->pm_check.return_value = 0;
			++diff;
		}
		++idx;
	}
	if (diff == 0)
	{
		s2[r_idx] = '\0';
		info->pm_check.l_pm_pos += 1;
		info->pm_check.return_value = 1;
	}
}
