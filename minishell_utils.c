/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:26:57 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/18 22:19:12 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_io.h"
#include "libft.h"
#include <errno.h>
#include <string.h>

// prefix-> cmd;
// parameter-> argv or param
// msg-> cause
int	print_error(char *prefix, char *parameter, char *msg)
{
	if (prefix)
	{
		puterr_safe(prefix);
		puterr_safe(": ");
	}
	if (parameter)
	{
		puterr_safe(parameter);
		puterr_safe(": ");
	}
	if (errno != 0)
	{
		msg = strerror(errno);
		errno = 0;
	}
	puterr_safe(msg);
	puterr_safe("\n");
	return (-1);
}
