/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:06:56 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/30 19:40:27 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "built_in.h"

size_t	ft_pwd(void)
{
	char buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)))
	{
		ft_putstr_nl(buf, 1);
		return (0);
	}
	else
		return (-1);
}

char	*get_pwd(void)
{
	char *buf;

	buf = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
	if (!buf)
		return (NULL);
	if (getcwd(buf, sizeof(buf)))
		return (buf);
	else
		return (NULL);
}
