/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_jobs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:33:05 by jkong             #+#    #+#             */
/*   Updated: 2022/06/20 03:52:15 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_io.h"
#include "safe_mem.h"
#include "generic_list.h"
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

pid_t	make_child(t_shell *sh)
{
	pid_t			pid;
	t_list_process	*next;

	pid = fork();
	if (pid < 0)
	{
		puterr_safe("fork\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		while (sh->pid_list)
		{
			next = sh->pid_list->next;
			free(sh->pid_list);
			sh->pid_list = next;
		}
	}
	else
	{
		next = calloc_safe(1, sizeof(*next));
		next->pid = pid;
		list_append((void *)&sh->pid_list, (void *)next);
	}
	return (pid);
}

static int	_get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (WEXITSTATUS(status));
}

int	wait_for(t_shell *sh, pid_t pid)
{
	pid_t			got_pid;
	t_list_process	*next;
	int				status;

	sh->exit_status = -1;
	sh->pid_list = (void *)list_reverse((void *)sh->pid_list);
	while (sh->pid_list)
	{
		next = sh->pid_list->next;
		got_pid = waitpid(sh->pid_list->pid, &status, 0);
		if (got_pid < 0)
		{
			puterr_safe("waitpid\n");
			exit(EXIT_FAILURE);
		}
		if (got_pid == pid)
			sh->exit_status = _get_exit_status(status);
		free(sh->pid_list);
		sh->pid_list = next;
	}
	return (sh->exit_status);
}
