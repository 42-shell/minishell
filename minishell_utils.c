/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:36:06 by jkong             #+#    #+#             */
/*   Updated: 2022/06/22 21:48:32 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_io.h"
#include "string_buffer.h"

void	print_err(const char *format, ...)
{
	va_list		ap;
	t_str_buf	*buf;
	char		*str;

	va_start(ap, format);
	buf = str_append_format_v(NULL, format, &ap);
	va_end(ap);
	str = str_dispose(buf);
	puterr_safe(str);
	free(str);
}
