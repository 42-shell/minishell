/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:49:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/11 18:14:11 by yongmkim         ###   ########.fr       */
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
	t_generic_list	*head;
	char			*temp;

	printf("%lu %lu %lu\n", sizeof(t_generic_list), sizeof(char *), sizeof(char **));
	head = (t_generic_list *)malloc(sizeof(t_generic_list) + sizeof(char *) + sizeof(char **));
	printf("%lu %lu\n", sizeof(head), sizeof(temp));
	head[1] = *(t_generic_list *)strdup("world");
	temp = strdup("hello");
	printf("%s\n", temp);
	temp = (char *)head[1];
	printf("%s\n", (char *)head[1]);
	// print list
	return (0);
}
