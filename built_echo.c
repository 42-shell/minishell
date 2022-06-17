/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 21:31:58 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/17 16:10:13 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"
#include "string_buffer.h"
#include "safe_io.h"

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

// need to use str_buff 
// change to readable
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
		putstr_safe(argv[idx]);
		if (argv[idx + 1])
			putstr_safe(" ");
		++idx;
	}
	if (!opt)
		putstr_safe("\n");
	return (0);
}
