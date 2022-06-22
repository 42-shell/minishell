/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:10:38 by jkong             #+#    #+#             */
/*   Updated: 2022/06/22 19:33:43 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*find_command(t_shell *sh, char *name)
{
	char	*path_list;
	char	*next_path;

	path_list = get_var(sh->var_list, "PATH", 1);
	while (path_list)
	{
		next_path = ft_strchr(path_list, ':');
		if (next_path)
			*next_path = '\0';
		//path = path_list
		path_list = next_path;
	}
}
