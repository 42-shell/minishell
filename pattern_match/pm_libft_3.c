/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_libft_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:25:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/04 23:26:56 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*temp_dst;

	if (!src && !dst)
		return (NULL);
	temp_dst = (unsigned char *)dst;
	while (n--)
	{
		*(temp_dst++) = *((unsigned char *)src++);
	}
	return (dst);
}

static void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;

	temp = b;
	while (len--)
	{
		*(temp++) = (unsigned char)c;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

char	*ft_strchr(const char *s, int c)
{
	char	*temp;

	temp = (char *)s;
	while (1)
	{
		if (*temp == (char)c)
			return (temp);
		if (*temp == '\0')
			return (NULL);
		temp++;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return (NULL);
	temp[len] = 0;
	ft_memcpy(temp, s + start, len);
	return (temp);
}
