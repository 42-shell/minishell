/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:26:57 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 16:41:01 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_io.h"
#include "libft.h"
#include <errno.h>
#include <string.h>
#include "string_buffer.h"

// prefix-> cmd; parameter-> argv or param; msg-> cause
int	print_error(char *prefix, char *parameter, char *msg, int return_value)
{
	t_str_buf	*sb;

	sb = NULL;
	sb = str_append(sb, "minishell: ");
	if (prefix)
	{
		sb = str_append(sb, prefix);
		sb = str_append(sb, ": ");
	}
	if (parameter)
	{
		sb = str_append(sb, parameter);
		sb = str_append(sb, ": ");
	}
	if (errno != 0)
	{
		msg = strerror(errno);
		errno = 0;
	}
	sb = str_append(sb, msg);
	sb = str_append(sb, "\n");
	msg = str_dispose(sb);
	puterr_safe(msg);
	free(msg);
	return (return_value);
}
