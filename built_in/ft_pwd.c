/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:06:56 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/22 23:16:11 by yongmkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_pwd(void)
{
	char *buf;

	buf = (char *)malloc(sizeof(char) * 256);
	if (!buf)
		return (-1);
	buf[255] = '\0';
	if (getcwd(buf, sizeof(buf)))
	{
		ft_putstr_nl(buf, 1);
		free(buf);
		return (0);
	}
	else
		return (-1);
}
