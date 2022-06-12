/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:37:07 by jkong             #+#    #+#             */
/*   Updated: 2022/05/25 21:13:50 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_buffer.h"

/*
static void	*_memcpy(void *dst, const void *src, size_t n)
{
	const size_t		long_n = n / sizeof(long);
	size_t				i;

	if (src != dst)
	{
		i = 0;
		while (i < long_n)
		{
			((long *)dst)[i] = ((const long *)src)[i];
			i++;
		}
		i *= sizeof(long);
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}
*/

static void	*_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (src != dst)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

static void	_resize_buffer(t_str_buf *buf, size_t n)
{
	size_t	capacity;
	char	*attach;
	char	*detach;

	capacity = buf->capacity;
	if (capacity == 0)
		capacity = INITIAL_CAPACITY;
	while (capacity < buf->length + n)
	{
		if (capacity < GROW_THRESHOLD)
			capacity <<= 1;
		else
			capacity += GROW_THRESHOLD;
	}
	if (capacity != buf->capacity)
	{
		attach = malloc_safe(capacity);
		detach = buf->str;
		_memcpy(attach, detach, buf->length);
		buf->str = attach;
		free(detach);
		buf->capacity = capacity;
	}
}

t_str_buf	*str_append_raw(t_str_buf *buf, const char *s, size_t n)
{
	if (buf == NULL)
		buf = calloc_safe(1, sizeof(t_str_buf));
	_resize_buffer(buf, n);
	_memcpy(&buf->str[buf->length], s, n);
	buf->length += n;
	return (buf);
}

t_str_buf	*str_append(t_str_buf *buf, const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (str_append_raw(buf, s, i));
}

char	*str_dispose(t_str_buf *buf)
{
	char	*result;

	if (!buf)
		return (NULL);
	result = calloc_safe(buf->length + 1, sizeof(char));
	_memcpy(result, buf->str, buf->length);
	free(buf->str);
	free(buf);
	return (result);
}
