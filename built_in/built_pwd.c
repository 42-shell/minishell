/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:06:56 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/15 15:40:21 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include <stdlib.h>
#include <unistd.h>

size_t	ft_pwd(char **argv)
{
	char	*buf;

	if (ft_getarr_size(argv) != 1)
		return (-1);
	buf = getcwd(NULL, 0);
	if (buf)
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
	return (getcwd(NULL, 0));
}
