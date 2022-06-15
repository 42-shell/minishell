/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:25:54 by jkong             #+#    #+#             */
/*   Updated: 2022/06/15 21:18:22 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_io.h"

int	read_safe(int fd, void *buf, size_t len)
{
	size_t	off;
	ssize_t	res;

	off = 0;
	while (off < len)
	{
		res = read(fd, buf + off, len - off);
		if (res < 0)
			exit(EXIT_FAILURE);
		if (res == 0)
			return (0);
		off += res;
	}
	return (1);
}

void	write_safe(int fd, const void *buf, size_t len)
{
	size_t	off;
	ssize_t	res;

	off = 0;
	while (off < len)
	{
		res = write(fd, buf + off, len - off);
		if (res < 0)
			exit(EXIT_FAILURE);
		off += res;
	}
}
