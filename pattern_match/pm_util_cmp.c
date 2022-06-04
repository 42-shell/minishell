/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_util_cmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:35:44 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/04 11:39:10 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include "libft.h"

void	pm_cmp_strstr(t_pattern_info *info, char *name, int pm_pos, int na_pos)
{
	int	size;

	size = ft_strlen(info->pattern_split[pm_pos]);
	if (ft_strnstr(&name[na_pos], info->pattern_split[pm_pos], size))
	{
		info->pm_check.l_pm_pos += 1;
		info->pm_check.l_name_pos += size;
	}
	else
	{
		info->pm_check.l_pm_pos = info->pm_check.r_pm_pos + 1;
	}
}

int	check_dot_dot(char *name, int type)
{
	if (type == PM_DIRECTORY)
	{
		if (!(ft_strncmp(name, ".", ft_strlen(name))) \
			|| !(ft_strncmp(name, "..", ft_strlen(name))))
			return (1);
	}
	return (0);
}
