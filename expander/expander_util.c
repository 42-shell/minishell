/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:16:50 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/14 15:38:20 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	ft_free_exp_info(t_exp_info *info)
{
	int	idx;

	idx = 0;
	while (info->exp_arr && info->exp_arr[idx])
	{
		free(info->exp_arr[idx]);
		idx++;
	}
	free(info->exp_arr);
}

// idx -> 0 : for init_value, reduce fn_line
int	create_expand_arr(t_exp_info *info, char *cpy_target, int idx)
{
	char	**temp;

	if (info->malloc_size > info->cur_pos + 1)
		info->exp_arr[info->cur_pos] = ft_strdup(cpy_target);
	else
	{
		info->malloc_size *= 2;
		temp = (char **)malloc(sizeof(char *) * info->malloc_size);
		if (!temp)
			return (-1);
		temp[info->malloc_size - 1] = NULL;
		idx = 0;
		while (info->exp_arr && info->exp_arr[idx])
		{
			temp[idx] = ft_strdup(info->exp_arr[idx]);
			idx++;
		}
		temp[idx] = ft_strdup(cpy_target);
		temp[idx + 1] = NULL;
		if (info->exp_arr)
			ft_free_exp_info(info);
		info->exp_arr = temp;
	}
	info->cur_pos += 1;
	return (0);
}
