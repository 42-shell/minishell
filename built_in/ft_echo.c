/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 21:31:58 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/22 22:44:11 by yongmkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static size_t	set_point(char ***argv, size_t pos)
{
	(*argv) = &(*argv)[pos];
	return (pos);
}

static size_t	check_opt(char ***argv)
{
	size_t	idx;
	size_t	pos;

	pos = 0;
	while ((*argv)[pos])
	{
		idx = 0;
		if (((*argv)[pos])[idx] == '-')
		{
			++idx;
			while (((*argv)[pos])[idx])
			{
				if (((*argv)[pos])[idx] != 'n')
					return (set_point(argv, pos));
				++idx;
			}
		}
		else
			return (set_point(argv, pos));
		++pos;
	}
	return (pos);
}

size_t	ft_echo(char **argv)
{
	size_t	opt;
	size_t	idx;

	if (!argv || !(*argv))
		return (-1);
	opt = check_opt(&argv);
	idx = 0;
	while (argv[idx])
	{
		ft_putstr_fd(argv[idx], 1);
		if (argv[idx + 1])
			ft_putchar_fd(' ', 1);
		++idx;
	}
	if (!opt)
		ft_putchar_fd('\n', 1);
	return (0);
}
