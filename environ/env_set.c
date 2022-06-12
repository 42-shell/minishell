/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:49:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/12 23:52:36 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_set.h"

/*
t_generic_list	env_set(char **env_str)
{
	t_generic_list	*head;
	t_generic_list	*temp;
	int				idx;
	char			*pos;

	idx = 0;
	head = NULL;
	while (env_str && env_str[idx])
	{
		pos = ft_strchr(env_str[idx], '=');
		temp + sizeof(t_generic_list) = ft_strndup(env_str[idx], pos - env_str[idx][0]);
		temp + (sizeof(t_generic_list) + sizeof(char *)) = ft_strdup(pos);
	}
	// 
	//
}
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
	int			i = 0;
	t_env_list	*head;
	
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	printf("--\n");
	head = NULL;
	head = env_set(envp);
	return (0);
}
