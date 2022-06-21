/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:54:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 15:24:32 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static t_str_buf	*_str_append_number(t_str_buf *sb, int n)
{
	const int		sign = n < 0;
	char			buf[11];
	const size_t	count = sizeof(buf) / sizeof(*buf);
	size_t			i;

	i = count;
	if (!n)
		buf[--i] = '0';
	while (n)
	{
		buf[--i] = '0' + (1 - (sign << 1)) * (n % 10);
		n /= 10;
	}
	if (sign)
		buf[--i] = '-';
	return (str_append_raw(sb, buf + i, count - i));
}

static void	expand_other_case(t_exp_info *info, char *str, size_t *ret)
{
	if (*(str + *ret) == '\0')
		info->sb = str_append_raw(info->sb, "$", 1);
	else if (*(str + *ret) == '\?')
	{
		info->sb = _str_append_number(info->sb, info->last_exit_status);
		*ret += 1;
	}
	else
		*ret += 1;
}

size_t	_dollar(t_exp_info *info, t_env_list *env, char *str)
{
	char	*expand;
	char	*temp;
	size_t	ret;

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
		temp = str_dispose(info->sb_dollar);
		expand = get_env(env, temp);
		if (expand)
			info->sb = str_append(info->sb, expand);
		free(temp);
		info->sb_dollar = NULL;
	}
	else
		expand_other_case(info, str, &ret);
	return (ret);
}

size_t	_s_quote(t_exp_info *info, char *str, int key)
{
	size_t	ret;

	ret = 1;
	while (1)
	{
		if (*(str + ret) == '\0')
			break ;
		if ((*(str + ret) == '\'') || (*(str + ret) == '`'))
		{
			ret++;
			break ;
		}
		else if (key == EXP_DEQUO || key == EXP_SUBST)
			info->sb = str_append_raw(info->sb, str + ret, 1);
		ret++;
	}
	return (ret);
}

size_t	_d_quote(t_exp_info *info, t_env_list *env, char *str, int key)
{
	size_t	ret;

	ret = 1;
	while (1)
	{
		if (*(str + ret) == '\0')
			break ;
		else if (*(str + ret) == '\"')
		{
			ret++;
			break ;
		}
		else
		{
			if (key == EXP_SUBST && *(str + ret) == '$')
				ret += _dollar(info, env, str + ret);
			else
			{
				if (key == EXP_DEQUO || key == EXP_SUBST)
					info->sb = str_append_raw(info->sb, str + ret, 1);
				ret++;
			}
		}
	}
	return (ret);
}
