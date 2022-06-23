/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_vector_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:37:07 by jkong             #+#    #+#             */
/*   Updated: 2022/06/23 17:36:34 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_vector.h"

size_t	length_strvec(char **arr)
{
	size_t	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static void	_swap_str(char **a, char **b)
{
	char	*x;

	if (a == b)
		return ;
	x = *a;
	*a = *b;
	*b = x;
}

void	sort_strvec(char **arr, int (*cmp)(const char *, const char *))
{
	size_t	len;
	size_t	i;

	len = length_strvec(arr);
	while (len > 1)
	{
		i = 0;
		while (i < len - 1)
		{
			if (cmp(arr[i], arr[i + 1]) > 0)
				_swap_str(&arr[i], &arr[i + 1]);
			i++;
		}
		len--;
	}
}

void	free_strvec(char **arr)
{
	char **const	vec = arr;

	if (arr)
		while (*arr)
			free(*arr++);
	free(vec);
}
