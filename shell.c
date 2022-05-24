/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:34:05 by jkong             #+#    #+#             */
/*   Updated: 2022/05/24 20:40:44 by yongmkim         ###   ########.fr       */
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
	ft_signal();
	while (1)
	{
		rl = readline("$ ");

		free(rl);
	}
	return (exit_status);
}
