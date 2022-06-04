/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:06:56 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/04 18:38:15 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "built_in.h"

size_t	ft_pwd(void)
{
	char buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)))
	{
		ft_putstr_fd(buf, 1);
		ft_putchar_fd('\n', 1);
		return (0);
	}
	else
		return (-1);
}

char	*ft_get_pwd(void)
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
