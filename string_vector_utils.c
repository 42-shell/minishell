/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_vector_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:37:07 by jkong             #+#    #+#             */
/*   Updated: 2022/06/21 13:31:29 by jkong            ###   ########.fr       */
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

void	free_strvec(char **arr)
{
	char **const	vec = arr;

	if (arr)
		while (*arr)
			free(*arr++);
	free(vec);
}
