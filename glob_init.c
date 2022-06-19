/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:36 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 02:24:01 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

static void	count_pattern_size(t_glob_info *info)
{
	size_t	i;
	size_t	cnt;
	char	*temp;

	i = 0;
	cnt = 0;
	while (info->pattern_split && info->pattern_split[i])
	{
		cnt += ft_strlen(info->pattern_split[i]);
		i++;
	}
	info->split_size = i;
	info->split_text_cnt = cnt;
	if (info->glob_flag.r_type == GLOB_SLASH)
	{
		temp = info->pattern_split[info->split_size - 1];
		temp[ft_strlen(temp) - 1] = '\0';
		if (info->split_text_cnt != 1)
			info->split_text_cnt -= 1;
	}
}

static void	glob_init(\
char *str, t_glob_info *info, t_str_vec *str_vec, t_env_list *env)
{
	info->glob_matched = str_vec;
	info->pwd = get_env(env, "PWD");
	if (str[0] == GLOB_ASTERISK)
		info->glob_flag.l_type = GLOB_ASTERISK;
	else if (str[0] == GLOB_DOT)
		info->glob_flag.l_type = GLOB_DOT;
	else
		info->glob_flag.l_type = GLOB_WORD;
	if (str[ft_strlen(str) - 1] == GLOB_ASTERISK)
		info->glob_flag.r_type = GLOB_ASTERISK;
	else if (str[ft_strlen(str) - 1] == GLOB_SLASH)
		info->glob_flag.r_type = GLOB_SLASH;
	else
		info->glob_flag.r_type = GLOB_WORD;
	info->pattern_split = ft_split(str, GLOB_ASTERISK);
}

// if return -> NULL -> print "pattern"
t_str_vec	*expand_glob(char *pattern, t_str_vec *str_vec, t_env_list *env)
{
	t_glob_info	info;

	if (!pattern || *pattern == '\0')
		return (NULL);
	glob_init(pattern, &info, str_vec, env);
	count_pattern_size(&info);
	if (glob_workhorse(&info, env))
		return (ft_free_pm(&info, RM_PATTERN_SPLIT | RM_STR_VEC));
	ft_free_pm(&info, RM_PATTERN_SPLIT);
	return (info.glob_matched);
}
