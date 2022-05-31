/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:15:25 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/31 21:16:51 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include "libft.h"
#include <stdlib.h>

void	pm_strcmp(t_pattern_info *info, ...)
{
}

int	create_inter(t_pattern_info *info, char *find)
{
	char	**temp;
	int		idx;

	if (info->malloc_size > info->pm_cnt + 1)
		info->pm_interleaving[info->pm_cnt + 1] = ft_strdup(find);
	else
	{
		info->malloc_size *= 2;
		temp = (char **)malloc(sizeof(char *) * info->malloc_size);
		if (!temp)
			return (-1);
		temp[info->malloc_size - 1] = NULL;
		idx = 0;
		while (info->pm_interleaving[idx])
		{
			temp[idx] = info->pm_interleaving[idx];
			++idx;
		}
		temp[idx] = ft_strdup(find);
		temp[idx + 1] = NULL;
		free(info->pm_interleaving);
		info->pm_interleaving = temp;
	}
	info->pm_cnt += 1;
	return (0);
}
