/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:25:54 by jkong             #+#    #+#             */
/*   Updated: 2022/06/23 22:48:50 by jkong            ###   ########.fr       */
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
	const unsigned char	c = 0;
	const long			l = 0L;
	size_t				i;

	i = 0;
	while (i < long_len)
		((long *)b)[i++] = l;
	i *= sizeof(long);
	while (i < len)
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

	return (_fill_zero(malloc_safe(final_size), final_size));
}

int	free_safe(void *ptr)
{
	free(ptr);
	return (0);
}
