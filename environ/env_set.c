/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:49:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 00:19:01 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_set.h"

t_env_list	env_set(char **env_str)
{
	t_env_list	*head;
	t_env_list	*temp;
	int			idx;
	char		*pos;

	idx = 0;
	head = NULL;
	while (env_str && env_str[idx])
	{
		pos = ft_strchr(env_str[idx], '=');
		temp = ft_strndup(env_str[idx], pos - env_str[idx][0]);
		temp = ft_strdup(pos);
	}
	return (head);
}

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
	//head = env_set(envp);
	return (0);
}
