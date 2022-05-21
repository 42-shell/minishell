/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:25:54 by jkong             #+#    #+#             */
/*   Updated: 2022/05/21 20:08:37 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_mem.h"

static void	*_required_non_null(void *ptr)
{
	if (!ptr)
		exit(EXIT_FAILURE);
	return (ptr);
}

static void	*_fill_zero(void *b, size_t len)
{
	const size_t		long_len = len / sizeof(long);
	const size_t		byte_len = len % sizeof(long);
	const unsigned char	c = 0;
	const long			l = 0L;
	size_t				i;

	i = 0;
	while (i < long_len)
		((long *)b)[i++] = l;
	i = 0;
	while (i < byte_len)
		((unsigned char *)b)[i++] = c;
	return (b);
}

void	*malloc_safe(size_t size)
{
	return (_required_non_null(malloc(size)));
}

void	*calloc_safe(size_t count, size_t size)
{
	const size_t	final_size = count * size;
	void			*ptr;

	ptr = malloc_safe(final_size);
	if (ptr)
		_fill_zero(ptr, final_size);
	return (ptr);
}
