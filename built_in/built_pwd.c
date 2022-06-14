/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:06:56 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/14 20:00:53 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include <stdlib.h>
#include <unistd.h>

size_t	ft_pwd(char **argv)
{
	char	buf[PATH_MAX];
	size_t	size;

	size = ft_getarr_size(argv);
	if (!size || size != 1)
		return (-1);
	if (getcwd(buf, sizeof(buf)))
	{
		ft_putstr_fd(buf, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	else
		return (-1);
}

char	*ft_get_pwd(void)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
	if (!buf)
		return (NULL);
	if (getcwd(buf, sizeof(buf)))
		return (buf);
	else
		return (NULL);
}
