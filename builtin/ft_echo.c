/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 21:31:58 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/22 22:23:42 by yongmkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static size_t	set_point(char ***cmd, size_t pos)
{
	(*cmd) = &(*cmd)[pos];
	return (pos);
}

static size_t	check_opt(char ***cmd)
{
	size_t	idx;
	size_t	pos;

	pos = 0;
	while ((*cmd)[pos])
	{
		idx = 0;
		if (((*cmd)[pos])[idx] == '-')
		{
			++idx;
			while (((*cmd)[pos])[idx])
			{
				if (((*cmd)[pos])[idx] != 'n')
					return (set_point(cmd, pos));
				++idx;
			}
		}
		else
			return (set_point(cmd, pos));
		++pos;
	}
	return (pos);
}

size_t	ft_echo(char **cmd)
{
	size_t	opt;
	size_t	idx;

	if (!cmd || !(*cmd))
		return (-1);
	opt = check_opt(&cmd);
	idx = 0;
	while (cmd[idx])
	{
		ft_putstr_fd(cmd, 1);
		if (cmd[idx + 1])
			ft_putchar_fd(' ', 1);
		++idx;
	}
	if (!opt)
		ft_putchar_fd('\n', 1);
	return (0);
}
