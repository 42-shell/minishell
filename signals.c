/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:46:29 by jkong             #+#    #+#             */
/*   Updated: 2022/06/25 14:24:04 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_io.h"

void	on_signal(void)
{
	putstr_safe("\n");
}

static void	_handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		on_signal();
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	g_exit_status = get_exit_status(sig);
}

static void	_assert_signal(void *ptr)
{
	if (ptr == SIG_ERR)
		exit(EXIT_FAILURE);
}

void	set_signal_handler(int state)
{
	if (state == -1)
	{
		_assert_signal(signal(SIGINT, SIG_DFL));
		_assert_signal(signal(SIGQUIT, SIG_DFL));
	}
	else
	{
		if (state == 1)
			_assert_signal(signal(SIGINT, _handle_signal));
		else if (state == 2)
			_assert_signal(signal(SIGINT, SIG_DFL));
		else
			_assert_signal(signal(SIGINT, SIG_IGN));
		_assert_signal(signal(SIGQUIT, SIG_IGN));
	}
}
