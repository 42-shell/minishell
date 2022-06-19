/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:49:02 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 00:18:14 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static size_t	_dollar(\
t_exp_info *info, t_env_list *env, char *str, size_t ret)
{
	char	*expand;
	char	*temp;

	if (legal_variable_starter(*(str + ret)))
	{
		info->sb_dollar = str_append_raw(info->sb_dollar, str + ret, 1);
		ret++;
		while (legal_variable_char(*(str + ret)))
		{
			info->sb_dollar = str_append_raw(info->sb_dollar, str + ret, 1);
			ret++;
		}
		temp = str_dispose(info->sb_dollar);
		expand = get_env(env, temp);
		if (expand)
			info->sb = str_append(info->sb, expand);
		free(temp);
		info->sb_dollar = NULL;
	}
	else if (*(str + ret) == '\0')
		info->sb = str_append_raw(info->sb, "$", 1);
	else
		expand_other_case(info, str, env, &ret);
	return (ret);
}

static size_t	_s_quote(t_exp_info *info, char *str)
{
	size_t	ret;

	ret = 1;
	while (1)
	{
		if ((*(str + ret) == '\0') || (*(str + ret) == '\'') \
		|| (*(str + ret) == '`'))
		{
			ret++;
			break ;
		}
		else
			info->sb = str_append_raw(info->sb, str + ret, 1);
		ret++;
	}
	return (ret);
}

static size_t	_d_quote(t_exp_info *info, t_env_list *env, char *str)
{
	size_t	ret;

	ret = 1;
	while (1)
	{
		if ((*(str + ret) == '\0') || (*(str + ret) == '\"'))
		{
			ret++;
			break ;
		}
		else
		{
			if (*(str + ret) == '$')
				ret += _dollar(info, env, str + ret, 1);
			else
			{
				info->sb = str_append_raw(info->sb, str + ret, 1);
				ret++;
			}
		}
	}
	return (ret);
}

static char	*expand_workhorse(t_exp_info *info, t_env_list *env, char *str)
{
	info->sb = str_append(info->sb, "");
	while (*str)
	{
		if (has_flag(get_char_flags(*str), CF_QUOTE))
		{
			if (*str == '\"')
				str += _d_quote(info, env, str);
			else if (*str == '\'' || *str == '`')
				str += _s_quote(info, str);
		}
		else if (has_flag(get_char_flags(*str), CF_EXPANSION))
			str += _dollar(info, env, str, 1);
		else
		{
			info->sb = str_append_raw(info->sb, str, 1);
			str++;
		}
	}
	return (str_dispose(info->sb));
}

char	**check_expand(char **argv, t_env_list *env)
{
	t_exp_info	info;
	char		*temp;

	info.sb_dollar = NULL;
	info.sv = NULL;
	info.cur_pos = 0;
	while (argv && argv[info.cur_pos])
	{
		info.sb = NULL;
		temp = expand_workhorse(&info, env, argv[info.cur_pos]);
		if (info.cur_pos && ft_strchr(temp, GLOB_ASTERISK))
		{
			info.sv = expand_glob(temp, info.sv, env);
			free(temp);
		}
		else
			info.sv = strv_append(info.sv, temp);
		info.cur_pos++;
	}
	return (strv_dispose(info.sv));
}
