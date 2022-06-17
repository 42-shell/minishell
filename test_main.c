/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:24:40 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/17 19:40:46 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "env_module.h"
#include "expander.h"
#include "libft.h"
#include <stdlib.h>

void	check_exit(void)
{
	system("leaks a.out");
}

int main(int argc, char **argv, char **envp)
{
	char		**str_arr = NULL;
	t_env_list	*temp;

	if (argc > 1)
	{
	//	atexit(check_exit);
		temp = set_env(envp);


		argv[2] = "env*";
		str_arr = check_expand(&argv[1], temp);
		int idx = 0;
		while (str_arr[idx])
		{
			printf("%s\n", str_arr[idx]);
			idx++;
		}
		/*
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
		*/
		clear_env(&temp);
	}
	return (0);
}
