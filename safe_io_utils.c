/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_io_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:25:54 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 09:45:39 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_io.h"

static size_t	_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	putstr_safe(const char *str)
{
	write_safe(STDOUT_FILENO, str, _strlen(str));
}

void	putnbr_safe(int n)
{
	const int		sign = n < 0;
	char			buf[11];
	const size_t	count = sizeof(buf) / sizeof(*buf);
	size_t			i;

	i = count;
	if (n == 0)
		buf[--i] = '0';
	while (n)
	{
		buf[--i] = '0' + (1 - (sign << 1)) * (n % 10);
		n /= 10;
	}
	if (sign)
		buf[--i] = '-';
	write_safe(STDOUT_FILENO, buf + i, count - i);
}

void	puterr_safe(const char *str)
{
	write_safe(STDERR_FILENO, str, _strlen(str));
}
