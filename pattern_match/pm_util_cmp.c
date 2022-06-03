/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_util_cmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:35:44 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/04 08:10:21 by yongmkim         ###   ########.fr       */
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
#include <stdio.h>

void	pm_strcmp_left(t_pattern_info *info, char *s1, char *s2)
{
}


void	pm_strcmp_right(t_pattern_info *info, char *s1, char *s2)
{
}

void	pm_strcmp_greedy(t_pattern_info *info, char *s1, char *s2)
{

}
