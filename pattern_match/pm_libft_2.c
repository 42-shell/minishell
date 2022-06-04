/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_libft_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:23:17 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/04 23:27:08 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_match.h"
#include <stdlib.h>

void	*ft_calloc(size_t cnt, size_t size)
{
	void	*temp;

	temp = malloc(cnt * size);
	if (!temp)
		return (NULL);
	ft_bzero(temp, cnt * size);
	return (temp);
}

static void	ft_errfree(char **temp)
{
	size_t	idx;

	idx = 0;
	while (temp[idx])
	{
		free(temp[idx]);
		idx++;
	}
	free(temp);
}

static size_t	ft_tokenlen(char const *s, char sep)
{
	size_t	str_flag;
	size_t	total_len;

	str_flag = 1;
	total_len = 0;
	if (!s)
		return (total_len);
	while (*s)
	{
		if (*s == sep)
		{
			str_flag = 1;
		}
		else if (str_flag == 1)
		{
			total_len++;
			str_flag = 0;
		}
		s++;
	}
	return (total_len);
}

static char	**ft_fill(char *s, char **temp, char sep, size_t t_len)
{
	size_t	idx;
	char	*rear;
	char	*front;

	idx = 0;
	front = s;
	while (idx < t_len)
	{
		if (*front != sep)
		{
			rear = ft_strchr(front, sep);
			if (!rear)
				rear = front + ft_strlen(front);
			temp[idx] = ft_substr(front, 0, rear - front);
			if (!temp[idx++])
			{
				ft_errfree(temp);
				return (NULL);
			}
			front = rear;
		}
		front++;
	}
	temp[idx] = NULL;
	return (temp);
}

char	**ft_split(char const *s, char c)
{
	char	**temp;
	size_t	total_len;

	if (!s)
		return (NULL);
	total_len = ft_tokenlen(s, c);
	temp = ft_calloc(total_len + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	if (total_len == 0)
	{
		temp[0] = NULL;
	}
	else
		ft_fill((char *)s, temp, c, total_len);
	return (temp);
}
