/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:54:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 06:41:18 by jkong            ###   ########.fr       */
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

void	expand_other_case(t_exp_info *info, char *str, size_t *ret)
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
