/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:34:05 by jkong             #+#    #+#             */
/*   Updated: 2022/05/21 14:33:15 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

int	main(int argc, char *argv[])
{
	char	*rl;
	int		exit_status;

	(void)&argc;
	(void)&argv;
	exit_status = 0;
	while (1)
	{
		rl = readline("$ ");
		free(rl);
	}
	return (exit_status);
}
