/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:31:13 by jkong             #+#    #+#             */
/*   Updated: 2022/06/20 22:19:21 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && n > 0 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n > 0)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}

char	*ft_strdup(const char *s)
{
	const size_t	len = ft_strlen(s) + 1;

	return (ft_memcpy(calloc_safe(len, sizeof(char)), s, len));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char const	*src;
	size_t		src_len;
	size_t		dst_len;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (start > src_len)
		start = src_len;
	src = &s[start];
	dst_len = ft_strlen(src);
	if (dst_len > len)
		dst_len = len;
	return (ft_memcpy(calloc_safe(dst_len + 1, sizeof(char)), src, dst_len));
}
