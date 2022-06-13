/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:24:40 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 22:22:38 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include <stdlib.h>

void	check_exit(void)
{
	system("leaks a.out");
}

int main(int argc, char **argv, char **envp)
{
	char		**str_arr;
	t_env_list	*temp;

	str_arr = (char **)malloc(sizeof(char *) * 2);
	str_arr[1] = NULL;
	str_arr[0] = argv[0];
//	atexit(check_exit);
	temp = set_env(envp);
	if (!ft_strcmp(argv[1], "env"))
	{
		ft_env(&argv[1], temp);
	}
	if (!ft_strcmp(argv[1], "unset"))
	{
		ft_env(str_arr, temp);
		ft_unset(&argv[1], &temp);
		printf("\n----\n\n");
		ft_env(str_arr, temp);
	}
	if (!ft_strcmp(argv[1], "export"))
	{
		printf("ret = %lu \n", ft_export(&argv[1], temp));
		printf("\n----\n\n");
		ft_env(str_arr, temp);
		printf("\n----\n\n");
		ft_export(str_arr, temp);
	}
	free(str_arr);
	clear_env(&temp);
	return (0);
}
