/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:03:10 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/11 17:21:02 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_set.h"
#include <stddef.h>

char	*ft_strchr(char *s, int c)
{
	char	*temp;

	if (!s || !(*s))
		return (0);
	temp = s;
	while (*temp)
	{
		if (*temp == (char)c)
			return (temp);
		temp++;
	}
	return (NULL);
}

size_t	get_strarr_size(char **target)
{
	size_t	idx;

	if (!target || !(*target))
		return (0);
	idx = 0;
	while (target[idx])
		idx++;
	return (idx);
}
