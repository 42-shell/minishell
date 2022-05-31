/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:36 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/31 11:46:35 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include "built_in.h"
#include "libft.h"
#include <stdlib.h>

static void	end_check(char *str, t_pattern_match *info)
{
	if (str[0] == PM_ASTERISK)
		info->l_type = PM_ASTERISK;
	else
		info->l_type = PM_WORD;
	if (str[ft_strlen(str) - 1] == PM_ASTERISK)
		info->r_type = PM_ASTERISK;
	else if (str[ft_strlen(str) - 1] == PM_SLASH)
		info->r_type = PM_SLASH;
	else
		info->r_type = PM_WORD;
	info->pm_idx = 0;
}

static int	ft_count_entity(t_pattern_match *info)
{
	int	idx;

	idx = 0;
	while (info->temp[idx])
		++idx;
	info->mark_pm = (char *)malloc(sizeof(char) * (idx + 1));
	if (!(info->mark_pm))
		return (-1);
	ft_memset(info->mark_pm, 0, idx);
	info->mark_pm[idx] = '\0';
	return (0);
}

static char **ft_free_pm(t_pattern_match *info, int key)
{
	int idx;

	idx = 0;
	if (key & 1)
	{
		while (info->temp[idx])
		{
			free(info->temp[idx]);
			++idx;
		}
		free(info->temp);
	}
	return (NULL);
}

char	**ft_pattern_match(char *pattern)
{
	t_pattern_match	info;

	if (!pattern || *pattern == '\0')
		return (NULL);
	info.pwd = get_pwd();
	if (!info.pwd)
		return (NULL);
	end_check(pattern, &info);
	info.temp = ft_split(pattern, PM_ASTERISK);
	if (!info.temp)
		return (NULL);
	if (ft_count_entity(&info))
		return (ft_free_pm(&info, 1));
	ft_pm_workhorse(&info, pattern);
	// 1. find pm (check pm_idx)
	// 2. malloc ** interleaving
	// 3. check mark_pm, ft_strdup target string to interleaving
	// 4. free temp
}
