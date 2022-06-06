/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:05:35 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/06 21:37:48 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_sig.h"

static void	ft_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		// ctrl + c
	}
	else if (sig_num == SIGQUIT)
	{
		// ctrl + \
	}
	else
		g_sig = 0;
}

int	ft_sig_set(void)
{
	if (signal(SIGINT, ft_handler) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, ft_handler) == SIG_ERR)
		return (1);
	return (0);
}
