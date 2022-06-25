/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_buffer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:37:07 by jkong             #+#    #+#             */
/*   Updated: 2022/06/25 13:24:16 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_buffer.h"
#include <stdarg.h>

t_str_buf	*str_append_number(t_str_buf *buf, int n)
{
	const int		sign = n < 0;
	char			arr[11];
	const size_t	count = sizeof(arr) / sizeof(*arr);
	size_t			i;

	i = count;
	if (n == 0)
		arr[--i] = '0';
	while (n)
	{
		arr[--i] = '0' + (1 - (sign << 1)) * (n % 10);
		n /= 10;
	}
	if (sign)
		arr[--i] = '-';
	return (str_append_raw(buf, arr + i, count - i));
}

t_str_buf	*str_append_character(t_str_buf *buf, char c)
{
	return (str_append_raw(buf, &c, sizeof(c)));
}

t_str_buf	*str_append_nullable(t_str_buf *buf, char *s, char *def)
{
	if (!s)
		s = def;
	return (str_append(buf, s));
}

t_str_buf	*str_append_format(t_str_buf *buf, const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	buf = str_append_format_v(buf, format, &ap);
	va_end(ap);
	return (buf);
}

t_str_buf	*str_append_format_v(t_str_buf *buf, const char *format,
	va_list *ap_ptr)
{
	size_t	i;

	while (*format != '\0')
	{
		i = 0;
		while (format[i] != '\0' && format[i] != '%')
			i++;
		buf = str_append_raw(buf, format, i);
		format += i;
		if (*format == '%')
		{
			format++;
			if (*format == 's')
				buf = str_append(buf, va_arg(*ap_ptr, char *));
			else if (*format == 'c')
				buf = str_append_character(buf, va_arg(*ap_ptr, int));
			else if (*format == 'd' || *format == 'i')
				buf = str_append_number(buf, va_arg(*ap_ptr, int));
			format++;
		}
	}
	return (buf);
}
