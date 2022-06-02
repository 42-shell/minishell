/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:38:28 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/02 22:09:55 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pattern_match.h"


int main(int argc, char **argv)
{
	char **temp;

	if (argc >= 2)
	{
		temp = ft_pattern_match(argv[1]);
		int idx = 0;
		printf("\n\n");
		while (temp[idx])
		{
			printf("%s\n", temp[idx]);
			free(temp[idx]);
			++idx;
		}
		free(temp);
	}
	return (0);
}
