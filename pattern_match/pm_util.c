/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:35:44 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/15 15:48:32 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include "pattern_match_enum.h"
#include "built_in.h"
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

int	check_dot_dot(char *name, int type)
{
	if (type == DT_DIR)
	{
		if (!(ft_strncmp(name, ".", ft_strlen(name))) \
			|| !(ft_strncmp(name, "..", ft_strlen(name))))
			return (1);
	}
	return (0);
}

void	count_split_size(t_pattern_info *info)
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
