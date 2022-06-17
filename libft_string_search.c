/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string_search.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:33:04 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/17 21:00:59 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*temp;

	if (!s || *s == '\0')
		return (NULL);
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		if (*s1 == '\0' || *s2 == '\0')
			break ;
		s1++;
		s2++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	need_len;
	size_t	hay_len;

	hay_len = ft_strlen(haystack);
	need_len = ft_strlen(needle);
	if (need_len == 0)
		return ((char *)haystack);
	if ((need_len > len) || (hay_len == 0) || (need_len > hay_len))
		return (NULL);
	if (hay_len < len)
		len = hay_len;
	while (len >= need_len)
	{
		if (ft_strncmp(haystack, needle, need_len) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
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
	temp = calloc_safe(len + 1, sizeof(char));
	if (!temp)
		return (NULL);
	temp[len] = 0;
	ft_memcpy(temp, s + start, len);
	return (temp);
}

size_t	ft_getarr_size(char **str_vec)
{
	size_t	idx;

	idx = 0;
	while (str_vec && str_vec[idx])
		idx++;
	return (idx);
}
