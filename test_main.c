/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:24:40 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 00:07:53 by yongmkim         ###   ########.fr       */
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
	char		**temp_arr;
	t_env_list	*temp;
	int			idx = 0;

	if (argc > 1)
	{
		printf("%s\n", argv[2]);
		//	atexit(check_exit);
		//
		temp_arr = (char **)malloc(sizeof(char *) * 2);
		temp_arr[1] = NULL;
		temp_arr[0] = ft_strdup("test");
		temp = set_env(envp);
		add_env(temp, "A", "", NON_VISIBLE);
		add_env(temp, "B", "", ON_VISIBLE);
		add_env(temp, "C", "", HIDE_VISIBLE);
		str_arr = check_expand(&argv[1], temp);
		printf("org --> \n");
		ft_echo(argv, temp);
		printf("\nexpand -->\n");
		ft_echo(str_arr, temp);
		printf("\n-----\n\n");

		if (!ft_strcmp(argv[1], "env"))
		{
			ft_env(str_arr, temp);
			printf("-> exit_status : %s\n", get_env(temp, "EXIT_STATUS"));
		}
		else if (!ft_strcmp(argv[1], "export"))
		{
			ft_env(temp_arr, temp);
			printf("\n----\n");
			ft_export(str_arr, temp);
			printf("-> exit_status : %s\n", get_env(temp, "EXIT_STATUS"));
			printf("\n----\n");
			ft_env(temp_arr, temp);
		}
		else if (!ft_strcmp(argv[1], "echo"))
		{
			ft_echo(str_arr, temp);
			printf("-> exit_status : %s\n", get_env(temp, "EXIT_STATUS"));
		}
		else if (!ft_strcmp(argv[1], "pwd"))
		{
			ft_pwd(temp_arr, temp);
			printf("-> exit_status : %s\n", get_env(temp, "EXIT_STATUS"));
		}
		else if (!ft_strcmp(argv[1], "unset"))
		{
			ft_env(temp_arr, temp);
			ft_unset(str_arr, &temp);
			printf("-> exit_status : %s\n", get_env(temp, "EXIT_STATUS"));
			printf("\n----\n");
			ft_env(temp_arr, temp);
		}
		else if (!ft_strcmp(argv[1], "cd"))
		{
			ft_pwd(temp_arr, temp);
			printf("%zu\n", ft_cd(str_arr, temp));
			printf("-> exit_status : %s\n", get_env(temp, "EXIT_STATUS"));
			ft_pwd(temp_arr, temp);
		}
		else if (!ft_strcmp(argv[1], "printenv"))
		{
			printf("%s\n", get_env(temp, argv[2]));
			printf("-> exit_status : %s\n", get_env(temp, "EXIT_STATUS"));
		}
		else if (!ft_strcmp(argv[1], "exit"))
		{
			ft_exit(str_arr, temp);
			printf("-> exit_status : %s\n", get_env(temp, "EXIT_STATUS"));
		}

		clear_env(&temp);
	}
	return (0);
}
