/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:26:57 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/18 22:04:08 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_io.h"
#include "libft.h"
#include <errno.h>
#include <string.h>

int	print_error(char *prefix, char *parameter, char *msg)
{
	if (prefix)
	{
		write_safe(2, prefix, ft_strlen(prefix));
		write_safe(2, ": ", 2);
	}
	if (parameter)
	{
		write_safe(2, parameter, ft_strlen(parameter));
		write_safe(2, ": ", 2);
	}
	if (errno != 0)
	{
		msg = strerror(errno);
		errno = 0;
	}
	write_safe(2, msg, ft_strlen(msg));
	write_safe(2, "\n", 1);
	return (-1);
}
