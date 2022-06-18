/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_pipeline.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:42:03 by jkong             #+#    #+#             */
/*   Updated: 2022/06/18 22:01:27 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_io.h"
#include <unistd.h>

static void	_first_pipe(t_command *cmd, int pipe_in, int pipe_out)
{
	execute_command(cmd, pipe_in, pipe_out);
	if (pipe_in != NO_PIPE)
		close(pipe_in);
	close(pipe_out);
}

static int	_last_pipe(t_command *cmd, int pipe_in, int pipe_out)
{
	int	exec_result;

	exec_result = execute_command(cmd, pipe_in, pipe_out);
	if (pipe_in != NO_PIPE)
		close(pipe_in);
	return (exec_result);
}

int	execute_pipeline(t_command *cmd, int pipe_in, int pipe_out)
{
	int			fildes[2];
	int			prev;
	t_command	*cur;

	prev = pipe_in;
	cur = cmd;
	while (cur->type == CMD_CONNECTION && cur->value.ptr
		&& cur->value.connection->connector == TK_OR)
	{
		if (pipe(fildes) < 0)
		{
			puterr_safe("pipe error");
			exit(EXIT_FAILURE);
		}
		_first_pipe(&cur->value.connection->first, prev, fildes[STDOUT_FILENO]);
		prev = fildes[STDIN_FILENO];
		cur = &cur->value.connection->second;
	}
	return (_last_pipe(cur, prev, pipe_out));
}
