/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:38:28 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/04 17:02:56 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pattern_match.h"

// gcc main.c pattern_match.c pm_util.c pm_util_cmp.c libft.a -g
int main(int argc, char **argv)
{
	char **temp;

	if (argc >= 2)
	{
		temp = ft_pattern_match(argv[1]);
		int idx = 0;
		while (temp && temp[idx])
		{
			printf("%s\n", temp[idx]);
			++idx;
		}
		idx = 0;
		while (temp && temp[idx])
		{
			free(temp[idx]);
			idx++;
		}
		free(temp);
	}
	return (0);
}
