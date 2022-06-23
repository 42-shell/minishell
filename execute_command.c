/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:35:53 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 04:05:16 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_vector.h"
#include <unistd.h>
#include <sys/wait.h>

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (WEXITSTATUS(status));
}

static int	_execute_subshell(t_shell *sh, t_command *cmd,
	int pipe_in, int pipe_out)
{
	t_subshell_command *const	val = cmd->value.subshell;
	pid_t						pid;

	pid = make_child(sh);
	if (pid == 0)
	{
		do_piping(pipe_in, pipe_out, sh->next_pipe);
		if (do_redirections(val->redirect_list, sh) < 0)
			exit(EXIT_FAILURE);
		exit(execute_command(sh, &val->container, NO_PIPE, NO_PIPE));
	}
	else
	{
		if (pipe_out == NO_PIPE)
			return (wait_for(sh, pid));
		return (EXIT_SUCCESS);
	}
}

static int	_execute_command_connection(t_shell *sh, t_command *cmd,
	int pipe_in, int pipe_out)
{
	t_command_connection *const	val = cmd->value.connection;
	int							exec_result;

	if (val->connector == TK_OR)
	{
		exec_result = execute_pipeline(sh, cmd, pipe_in, pipe_out);
	}
	else if (val->connector == TK_AND_AND)
	{
		exec_result = execute_command(sh, &val->first, pipe_in, pipe_out);
		if (exec_result == EXIT_SUCCESS)
			exec_result = execute_command(sh, &val->second, pipe_in, pipe_out);
	}
	else if (val->connector == TK_OR_OR)
	{
		exec_result = execute_command(sh, &val->first, pipe_in, pipe_out);
		if (exec_result != EXIT_SUCCESS)
			exec_result = execute_command(sh, &val->second, pipe_in, pipe_out);
	}
	else
	{
		print_err("Unsupported Connector: %d\n", val->connector);
		exit(EXIT_FAILURE);
	}
	return (exec_result);
}

int	execute_command(t_shell *sh, t_command *cmd, int pipe_in, int pipe_out)
{
	int	exec_result;

	if (cmd->type == CMD_SIMPLE)
		exec_result = execute_simple_command(sh, cmd, pipe_in, pipe_out);
	else if (cmd->type == CMD_SUBSHELL)
		exec_result = _execute_subshell(sh, cmd, pipe_in, pipe_out);
	else if (cmd->type == CMD_CONNECTION)
		exec_result = _execute_command_connection(sh, cmd, pipe_in, pipe_out);
	else
	{
		print_err("Unsupported Command %d\n", cmd->type);
		exit(EXIT_FAILURE);
	}
	return (exec_result);
}
