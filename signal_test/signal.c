/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 02:53:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/23 10:23:24 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_io.h"
#include <signal.h>
#include <readline/readline.h>

void	sig_handler_readline(int sig)
{
	if (sig == SIGINT)
	{
		putstr_safe("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		// set global_return_value, set 1
	}
}

void	sig_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		putstr_safe("\n");
		// need to exit?
		// return exit_value??
	}
}






void	set_signal_default(void)
{
	if (signal(SIGINT, sig_handler_readline) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}

void	set_signal_child(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(EXIT_FAILURE);
}

// == seg_sig_parent
void	set_signal_ign(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}

void	set_signal_heredoc(void)
{
	if (signal(SIGINT, sig_handler_heredoc) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}
