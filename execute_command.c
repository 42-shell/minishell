/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:35:53 by jkong             #+#    #+#             */
/*   Updated: 2022/06/22 22:29:55 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_vector.h"
#include <unistd.h>

static int	_execute_simple_command(t_shell *sh, t_command *cmd,
	int pipe_in, int pipe_out)
{
	const int	do_fork = pipe_in != NO_PIPE || pipe_out != NO_PIPE;
	pid_t		pid;
	int			exec_result;

	if (do_fork)
	{
		pid = make_child(sh);
		if (pid == 0)
			do_piping(pipe_in, pipe_out, sh->next_pipe);
		else
		{
			if (pipe_out == NO_PIPE)
				return (wait_for(sh, pid));
			return (EXIT_SUCCESS);
		}
	}
	else
		add_undo_redirects(sh);
	exec_result = execute_simple_command_internal(sh, cmd->value.simple,
			do_fork, pipe_out == NO_PIPE);
	if (do_fork)
		exit(exec_result);
	else
		cleanup_redirects(sh);
	return (exec_result);
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
		do_redirections(val->redirect_list);
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
		exec_result = _execute_simple_command(sh, cmd, pipe_in, pipe_out);
	else if (cmd->type == CMD_SUBSHELL)
		exec_result = _execute_subshell(sh, cmd, pipe_in, pipe_out);
	else if (cmd->type == CMD_CONNECTION)
		exec_result = _execute_command_connection(sh, cmd, pipe_in, pipe_out);
	else
	{
		print_err("Unsupported Command %d\n", cmd->type);
		exit(EXIT_FAILURE);
	}
	if (pipe_out == NO_PIPE)
		sh->exit_status = exec_result;
	return (exec_result);
}
