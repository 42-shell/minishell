/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_jobs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:33:05 by jkong             #+#    #+#             */
/*   Updated: 2022/06/18 17:14:04 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_io.h"
#include <unistd.h>

static int	_is_regular_fd(int fd)
{
	if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO)
		return (0);
	return (1);
}

void	do_piping(int pipe_in, int pipe_out)
{
	if (pipe_in != NO_PIPE)
	{
		if (dup2(pipe_in, STDIN_FILENO) < 0)
		{
			puterr_safe("dup\n");
			exit(EXIT_FAILURE);
		}
		if (_is_regular_fd(pipe_in))
			close(pipe_in);
	}
	if (pipe_out != NO_PIPE)
	{
		if (dup2(pipe_out, STDOUT_FILENO) < 0)
		{
			puterr_safe("dup\n");
			exit(EXIT_FAILURE);
		}
		if (_is_regular_fd(pipe_out))
			close(pipe_out);
	}
}

pid_t	make_child(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		puterr_safe("fork\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		putstr_safe("in the child\n");
	}
	else
	{
		putstr_safe("IN THE PARENT\n");
	}
	return (pid);
}

int	wait_for(pid_t pid)
{
	pid_t	got_pid;
	int		status;

	got_pid = waitpid(pid, &status, 0);
	if (got_pid < 0)
	{
		puterr_safe("waitpid\n");
		exit(EXIT_FAILURE);
	}
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (WEXITSTATUS(status));
}
