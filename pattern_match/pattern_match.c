/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:36 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/30 20:25:14 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include "built_in.h"
#include "libft.h"

static void	end_check(char *str, t_pattern_match *info)
{
	if (str[0] == PM_ASTERISK)
		info->l_type = PM_ASTERISK;
	else
		info->l_type = PM_WORD;
	if (str[sizeof(str) - 2] == PM_ASTERISK)
		info->r_type = PM_ASTERISK;
	else if (str[sizeof(str) - 2] == PM_SLASH)
		info->r_type = PM_SLASH;
	else
		info->r_type = PM_WORD;
	info->pm_idx = 0;
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
	info.interleaving = ft_split(pattern, PM_ASTERISK);
	// find pm_idx
	// malloc ** interleaving
	// redid find pm_idx and malloc str, set interleaving
	//
}

get_pwd();

