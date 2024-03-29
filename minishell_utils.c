/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:36:06 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 21:00:35 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_io.h"
#include "string_buffer.h"
#include <errno.h>
#include <string.h>

static void	_print_err_v(const char *format, va_list *ap)
{
	t_str_buf	*buf;
	char		*str;

	buf = str_append_format_v(NULL, format, ap);
	str = str_dispose(buf);
	puterr_safe(str);
	free(str);
}

void	print_err(const char *format, ...)
{
	va_list		ap;

	va_start(ap, format);
	_print_err_v(format, &ap);
	va_end(ap);
}

void	exit_fail(const char *s)
{
	print_err("%s: %s\n", s, strerror(errno));
	exit(EXIT_FAILURE);
}
