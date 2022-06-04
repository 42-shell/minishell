/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:41:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/04 18:39:10 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "built_in.h"

size_t	ft_cd(char *argv)
{
	if (!argv || !(*argv))
		return (-1);
	if (chdir(argv))
		return (-1);
	return (0);
}

/*
#include <stdio.h>
#include <stdlib.h>
int main()
{
	char *dir;

	while (1)
	{
		dir = malloc(sizeof(char) * 30);
		scanf("%s", dir);
		printf("input - %s\n", dir);
		if (ft_cd(dir))
			printf("error\n");
		system("pwd");
		free(dir);
	}
	return 0;
}
*/
