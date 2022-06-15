/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:31:13 by jkong             #+#    #+#             */
/*   Updated: 2022/06/15 17:40:34 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h> // malloc

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_getarr_size(char **argv)
{
	int	i;

	if (!argv || !(*argv))
		return (0);
	i = 0;
	while (argv[i])
		i++;
	return (i);
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
