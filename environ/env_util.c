/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:03:10 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 16:28:45 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include <stdlib.h>

size_t	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (1)
	{
		if (*s1 - *s2)
			return (*s1 - *s2);
		if (*s1 == '\0' && *s2 == '\0')
			return (0);
		s1++;
		s2++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
	{
		len++;
	}
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*temp;
	size_t	len;
	size_t	idx;

	idx = 0;
	len = ft_strlen(s1);
	if (!len)
		return (NULL);
	temp = malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (NULL);
	while (s1[idx])
	{
		temp[idx] = s1[idx];
		idx++;
	}
	temp[len] = '\0';
	return (temp);
}

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
