/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_pipeline.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:42:03 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 11:53:57 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_io.h"
#include <unistd.h>

static void	_first_pipe(t_shell *sh, t_command *cmd, int pipe_in, int pipe_out)
{
	execute_command(sh, cmd, pipe_in, pipe_out);
	if (pipe_in != NO_PIPE)
		close(pipe_in);
	close(pipe_out);
}

static int	_last_pipe(t_shell *sh, t_command *cmd, int pipe_in, int pipe_out)
{
	int	exec_result;

	sh->next_pipe = NO_PIPE;
	exec_result = execute_command(sh, cmd, pipe_in, pipe_out);
	if (pipe_in != NO_PIPE)
		close(pipe_in);
	if (pipe_out == NO_PIPE)
		(void)wait_for(sh, -1);
	return (exec_result);
}

int	execute_pipeline(t_shell *sh, t_command *cmd, int pipe_in, int pipe_out)
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
			exit_fail("pipe error\n");
		sh->next_pipe = fildes[STDIN_FILENO];
		_first_pipe(sh, &cur->value.connection->first,
			prev, fildes[STDOUT_FILENO]);
		prev = sh->next_pipe;
		cur = &cur->value.connection->second;
	}
	return (_last_pipe(sh, cur, prev, pipe_out));
}
