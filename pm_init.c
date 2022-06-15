/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:36 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/15 20:53:58 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pm.h"
#include "built_in.h" //getpwd
#include "libft.h"

static void	count_pattern_size(t_pattern_info *info)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (info->pattern_split && info->pattern_split[i])
	{
		cnt += ft_strlen(info->pattern_split[i]);
		i++;
	}
	info->split_size = i;
	info->split_text_cnt = cnt;
	if (info->pm_flag.r_type == PM_SLASH && info->split_text_cnt != 1)
		info->split_text_cnt -= 1;
}

static void	pm_set_flag(char *str, t_pattern_info *info)
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
	info->malloc_size = 1;
	info->pm_pos = 0;
	info->pm_matched = NULL;
}

// if return -> NULL -> print "pattern"
char	**find_pattern(char *pattern)
{
	t_pattern_info	info;

	if (!pattern || *pattern == '\0')
		return (NULL);
	info.pwd = ft_get_pwd();
	if (!info.pwd)
		return (NULL);
	pm_set_flag(pattern, &info);
	info.pattern_split = ft_split(pattern, PM_ASTERISK);
	if (!info.pattern_split)
		return (ft_free_pm(&info, RM_PWD));
	count_pattern_size(&info);
	if (pm_workhorse(&info))
		return (ft_free_pm(&info, RM_PWD | RM_PM | RM_PI));
	ft_free_pm(&info, RM_PWD | RM_PM);
	return (info.pm_matched);
}
