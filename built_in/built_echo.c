/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 21:31:58 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/14 19:49:44 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static size_t	set_point(char ***argv, size_t pos)
{
	(*argv) = &(*argv)[pos];
	return (pos);
}

static size_t	check_opt(char ***argv)
{
	size_t	idx;
	size_t	pos;

	(*argv) = &(*argv)[1];
	pos = 0;
	while ((*argv)[pos])
	{
		idx = 0;
		if (((*argv)[pos])[idx] == '-')
		{
			idx++;
			while (((*argv)[pos])[idx])
			{
				if (((*argv)[pos])[idx] != 'n')
					return (set_point(argv, pos));
				idx++;
			}
			if (idx == 1)
				return (set_point(argv, pos + 1));
		}
		else
			return (set_point(argv, pos));
		pos++;
	}
	return (set_point(argv, pos));
}

size_t	ft_echo(char **argv)
{
	size_t	opt;
	size_t	idx;

	idx = ft_getarr_size(argv);
	if (!idx)
		return (-1);
	opt = check_opt(&argv);
	idx = 0;
	while (argv[idx])
	{
		if (ft_putstr_fd(argv[idx], 1))
			return (-1);
		if (argv[idx + 1])
			if (ft_putstr_fd(" ", 1))
				return (-1);
		++idx;
	}
	if (!opt)
		if (ft_putstr_fd("\n", 1))
			return (-1);
	return (0);
}
