/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:35:44 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/04 23:51:58 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include <unistd.h>
#include <stdlib.h>

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

void	count_split_size(t_pattern_info *info)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (info->pattern_split && info->pattern_split[i])
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

char	*ft_get_pwd(void)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
	if (!buf)
		return (NULL);
	if (getcwd(buf, sizeof(buf)))
	{
		return (buf);
	}
	else
	{
		return (NULL);
	}
}
