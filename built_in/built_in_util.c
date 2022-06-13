/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:30:46 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 13:33:08 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include <unistd.h>

size_t	ft_getarr_size(char **argv)
{
	int	i;

	if (!argv || !(*argv))
		return (0);
	i = 0;
	while (argv[i])
		i++;
	return (i);
}

size_t	ft_putchar_fd(char c, int fd)
{
	if (!c)
		return (0);
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (0);
}

size_t	ft_putstr_fd(char *str, int fd)
{
	size_t	sum;
	size_t	idx;

	if (!str || !(*str))
		return (0);
	idx = 0;
	while (str[idx])
	{
		sum += ft_putchar_fd(str[idx], fd);
		idx++;
	}
	return (sum);
}
