/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:49:02 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/17 21:09:26 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static size_t	_dollar(t_exp_info *info, t_env_list *head, char *str, int key)
{
	size_t	ret;
	char	*expand;

	ret = 1;
	if (legal_variable_starter(*(str + ret)))
	{
		info->sb_dollar = str_append_raw(info->sb_dollar, str + ret, 1);
		ret++;
		while (legal_variable_char(*(str + ret)))
		{
			info->sb_dollar = str_append_raw(info->sb_dollar, str + ret, 1);
			ret++;
		}
		expand = get_env(head, str_dispose(info->sb_dollar));
		if (expand)
			info->sb = str_append(info->sb, expand);
		ret--;
		info->sb_dollar = NULL;
	}
	else if ((key & D_QUOTE) || (*(str + ret) == '\0'))
	{
		info->sb = str_append_raw(info->sb, "$", 1);
	}
	return (ret);
}

static size_t	_s_quote(t_exp_info *info, t_env_list *head, char *str)
{
	size_t	ret;

	ret = 1;
	while (1)
	{
		if (*(str + ret) == '\0')
		{
			//error 
			break ;
		}
		else if (*(str + ret) == '\'')
		{
			break ;
		}
		else
		{
			info->sb = str_append_raw(info->sb, str + ret, 1);
		}
		ret++;
	}
	return (ret);
}

static size_t	_d_quote(t_exp_info *info, t_env_list *head, char *str)
{
	size_t	ret;

	ret = 1;
	while (1)
	{
		if (*(str + ret) == '\0')
		{
			//error
			break ;
		}
		else if (*(str + ret) == '\"')
		{
			break ;
		}
		else
		{
			if (*(str + ret) == '$')
				ret += _dollar(info, head, str + ret, D_QUOTE);
			else
				info->sb = str_append_raw(info->sb, str + ret, 1);
		}
		ret++;
	}
	return (ret);
}

static char	*expand_workhorse(t_exp_info *info, t_env_list *head, char *str)
{
	while (*str)
	{
		if (has_flag(get_char_flags(*str), CF_QUOTE))
		{
			if (*str == '\"')
			{
				str += _d_quote(info, head, str);
			}
			else if (*str == '\'')
			{
				str += _s_quote(info, head, str);
			}
		}
		else if (has_flag(get_char_flags(*str), CF_EXPANSION))
		{
			str += _dollar(info, head, str, DOLLAR);
		}
		else
		{
			info->sb = str_append_raw(info->sb, str, 1);
			str++;
		}
	}
	return (str_dispose(info->sb));
}

char	**check_expand(char **argv, t_env_list *head)
{
	t_exp_info	info;
	char		*temp;

	if (!argv || !(*argv) || !head)
		return (NULL);
	info.sb_dollar = NULL;
	info.sv = NULL;
	info.cur_pos = 0;
	while (argv[info.cur_pos])
	{
		info.sb = NULL;
		temp = expand_workhorse(&info, head, argv[info.cur_pos]);
		if (info.cur_pos && ft_strchr(temp, PM_ASTERISK))
		{
			info.sv = expand_glob(temp, info.sv);
		}
		else
		{
			info.sv = strv_append(info.sv, temp);
		}
		info.cur_pos++;
	}
	return (strv_dispose(info.sv));
}
