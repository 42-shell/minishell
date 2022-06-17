/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:37:07 by jkong             #+#    #+#             */
/*   Updated: 2022/06/17 19:49:20 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_vector.h"

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

static void	_resize_vector(t_str_vec *vec, size_t n)
{
	size_t	capacity;
	char	**attach;
	char	**detach;

	capacity = vec->capacity;
	if (capacity == 0)
		capacity = INITIAL_CAPACITY_V;
	while (capacity < vec->length + n)
	{
		if (capacity < GROW_THRESHOLD_V)
			capacity <<= 1;
		else
			capacity += GROW_THRESHOLD_V;
	}
	if (capacity != vec->capacity)
	{
		attach = malloc_safe(capacity * sizeof(*vec->arr));
		detach = vec->arr;
		_memcpy(attach, detach, vec->length * sizeof(*vec->arr));
		vec->arr = attach;
		free(detach);
		vec->capacity = capacity;
	}
}

t_str_vec	*strv_append(t_str_vec *vec, char *s)
{
	const size_t	n = 1;

	if (vec == NULL)
		vec = calloc_safe(1, sizeof(t_str_vec));
	_resize_vector(vec, n);
	vec->arr[vec->length] = s;
	vec->length += n;
	return (vec);
}

t_str_vec	*strv_append_bulk(t_str_vec *vec, char **arr)
{
	size_t	i;
	size_t	n;

	if (vec == NULL)
		vec = calloc_safe(1, sizeof(t_str_vec));
	n = 0;
	while (arr[n])
		n++;
	_resize_vector(vec, n);
	i = 0;
	while (i < n)
	{
		vec->arr[vec->length] = arr[i];
		vec->length++;
		i++;
	}
	return (vec);
}

char	**strv_dispose(t_str_vec *vec)
{
	char	**result;

	if (!vec)
		return (NULL);
	result = calloc_safe(vec->length + 1, sizeof(*vec->arr));
	_memcpy(result, vec->arr, vec->length * sizeof(*vec->arr));
	free(vec->arr);
	free(vec);
	return (result);
}
