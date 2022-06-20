/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 20:47:42 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 22:07:52 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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
			elem = calloc_safe(i + 1, sizeof(char));
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
	result = calloc_safe(count + 1, sizeof(char *));
	if (result == NULL || !_split_elem(result, s, c))
		return (_split_free(result));
	return (result);
}
