/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_workhorse_shoe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:15:25 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 02:30:32 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"
#include <dirent.h> //DT macro

static void	init_check_info(t_glob_info *info, char *name)
{
	info->check_info.name_pos = 0;
	info->check_info.l_pt_pos = 0;
	info->check_info.r_pt_pos = (info->split_size);
	info->check_info.return_value = 0;
	info->check_info.cut_pos = 0;
	info->check_info.cut_char = name[0];
}

static void	cmp_middle(\
t_glob_info *info, char *name, size_t pt_pos, size_t na_pos)
{
	size_t	size;
	char	*pos;

	size = ft_strlen(&name[na_pos]);
	pos = ft_strnstr(&name[na_pos], info->pattern_split[pt_pos], size);
	if (pos)
	{
		info->check_info.l_pt_pos += 1;
		info->check_info.name_pos += (pos - &name[na_pos] + 1);
	}
	else
		info->check_info.l_pt_pos = info->check_info.r_pt_pos + 1;
}

static int	is_edge_str_equal(\
t_glob_info *info, char *name, int l_or_r, size_t idx)
{
	char	*temp;
	size_t	temp_len;

	temp = info->pattern_split[idx];
	temp_len = ft_strlen(temp);
	if (l_or_r == LHS)
	{
		if (temp_len == 0)
			return (0);
		return (!ft_strncmp(name, temp, temp_len));
	}
	else if (l_or_r == RHS)
		return (!ft_strncmp(&name[ft_strlen(name) - temp_len], temp, temp_len));
	return (0);
}

static void	cmp_edge(t_glob_info *info, char *name, int l_or_r, size_t idx)
{
	size_t	pos;

	if (info->check_info.r_pt_pos >= info->check_info.l_pt_pos)
	{
		if (is_edge_str_equal(info, name, l_or_r, idx))
		{
			if (l_or_r == LHS)
			{
				info->check_info.l_pt_pos++;
				info->check_info.name_pos = ft_strlen(info->pattern_split[idx]);
			}
			else if (l_or_r == RHS)
			{
				if (info->check_info.r_pt_pos != info->check_info.l_pt_pos)
					info->check_info.r_pt_pos--;
				pos = ft_strlen(name) - ft_strlen(info->pattern_split[idx]);
				info->check_info.cut_char = name[pos];
				info->check_info.cut_pos = pos;
				name[pos] = '\0';
			}
		}
		else
			info->check_info.l_pt_pos = info->check_info.r_pt_pos + 1;
	}
}

int	check_string(t_glob_info *info, char *name, int file_type)
{
	char	*temp;

	if (info->glob_flag.r_type == GLOB_SLASH && file_type != DT_DIR)
		return (1);
	if (info->glob_flag.l_type != GLOB_DOT && name[0] == '.')
		return (1);
	init_check_info(info, name);
	if (info->glob_flag.l_type == GLOB_WORD \
	|| info->glob_flag.l_type == GLOB_DOT)
		cmp_edge(info, name, LHS, 0);
	if (info->check_info.r_pt_pos < info->check_info.l_pt_pos)
		return (info->check_info.r_pt_pos - info->check_info.l_pt_pos);
	if ((info->glob_flag.r_type == GLOB_WORD \
	|| info->glob_flag.r_type == GLOB_SLASH))
		cmp_edge(info, name, RHS, info->check_info.r_pt_pos - 1);
	if (info->check_info.r_pt_pos < info->check_info.l_pt_pos)
		return (info->check_info.r_pt_pos - info->check_info.l_pt_pos);
	while (info->check_info.r_pt_pos > info->check_info.l_pt_pos)
		cmp_middle(info, name, info->check_info.l_pt_pos, \
		info->check_info.name_pos);
	return (info->check_info.r_pt_pos - info->check_info.l_pt_pos);
}
