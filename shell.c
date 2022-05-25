/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:34:05 by jkong             #+#    #+#             */
/*   Updated: 2022/05/25 17:27:08 by yongmkim         ###   ########.fr       */
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
		if (rl == NULL)
			return (exit_status);
		free(rl);
	}
	return (exit_status);
}
