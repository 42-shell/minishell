/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:06:56 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/15 19:07:24 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "string_buffer.h"
#include "libft.h" // getarr_size, print
#include <stdlib.h> // free
#include <unistd.h> // getcwd

size_t	ft_pwd(char **argv)
{
	char	*buf;

	if (ft_getarr_size(argv) != 1)
		return (-1);
	buf = getcwd(NULL, 0);
	if (buf)
	{
		putstr_safe(buf);
		putstr_safe("\n");
		free(buf);
		return (0);
	}
	else
		return (-1);
}

char	*ft_get_pwd(void)
{
	return (getcwd(NULL, 0));
}
