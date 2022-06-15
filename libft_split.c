/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 20:47:42 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/15 20:50:13 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

static void	*ft_calloc(size_t count, size_t size)
{
	size_t	final_size;
	void	*ptr;

	final_size = count * size;
	ptr = malloc(final_size);
	if (ptr)
		ft_bzero(ptr, final_size);
	return (ptr);
}

static int	_split_elem(char **ptr, char const *s, char c)
{
	int		i;
	char	*elem;

	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			i = 0;
			while (s[i] && s[i] != c)
				i++;
			elem = ft_calloc(i + 1, sizeof(char));
			*ptr++ = elem;
			if (elem == NULL)
				return (0);
			while (*s && *s != c)
				*elem++ = *s++;
			*elem = '\0';
		}
	}
	*ptr = NULL;
	return (1);
}

static char	**_split_free(char **ptr)
{
	char	**tab;

	if (ptr)
	{
		tab = ptr;
		while (*tab)
		{
			free(*tab);
			*tab++ = NULL;
		}
		free(ptr);
		ptr = NULL;
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		count;
	int		on_elem;
	int		i;

	if (!s)
		return (NULL);
	count = 0;
	on_elem = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			on_elem = 0;
		else if (!on_elem)
		{
			count++;
			on_elem = 1;
		}
		i++;
	}
	result = ft_calloc(count + 1, sizeof(char *));
	if (result == NULL || !_split_elem(result, s, c))
		return (_split_free(result));
	return (result);
}
