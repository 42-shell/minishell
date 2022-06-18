/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:35:53 by jkong             #+#    #+#             */
/*   Updated: 2022/06/18 22:03:47 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

#include <stdio.h>

extern char	**environ;

static int	_execute_simple_command(t_command *cmd, int pipe_in, int pipe_out)
{
	t_simple_command *const	val = cmd->value.simple;
	pid_t					pid;

	if (pipe_in == NO_PIPE && pipe_out == NO_PIPE)
		pid = 0;
	else
	{
		pid = make_child();
		if (pid == 0)
			do_piping(pipe_in, pipe_out);
		else
			return (wait_for(pid));
	}
	if (val->word_list)
		printf("SimpleCommand[%d, %d] %s\n",
			pipe_in, pipe_out, val->word_list->word.str);
	else
		printf("NullCommand\n");
	return (EXIT_SUCCESS);
}

static int	_execute_subshell(t_command *cmd, int pipe_in, int pipe_out)
{
	t_subshell_command *const	val = cmd->value.subshell;
	pid_t						pid;
	int							exit_value;

	pid = make_child();
	if (pid == 0)
	{
		do_piping(pipe_in, pipe_out);
		exit_value = execute_command(&val->container, pipe_in, pipe_out);
		exit(exit_value);
	}
	else
	{
		exit_value = EXIT_SUCCESS;
		if (pipe_out == NO_PIPE)
			exit_value = wait_for(pid);
	}
	return (exit_value);
}

static int	_execute_command_connection(t_command *cmd, int pipe_in,
	int pipe_out)
{
	t_command_connection *const	val = cmd->value.connection;
	int							exec_result;

	if (val->connector == TK_OR)
	{
		exec_result = execute_pipeline(cmd, pipe_in, pipe_out);
	}
	else if (val->connector == TK_AND_AND)
	{
		exec_result = execute_command(&val->first, pipe_in, pipe_out);
		if (exec_result == EXIT_SUCCESS)
			exec_result = execute_command(&val->second, pipe_in, pipe_out);
	}
	else if (val->connector == TK_OR_OR)
	{
		exec_result = execute_command(&val->first, pipe_in, pipe_out);
		if (exec_result != EXIT_SUCCESS)
			exec_result = execute_command(&val->second, pipe_in, pipe_out);
	}
	else
	{
		printf("Unsupported Connector: %d\n", val->connector);
		exit(EXIT_FAILURE);
	}
	return (exec_result);
}

int	execute_command(t_command *cmd, int pipe_in, int pipe_out)
{
	if (cmd->type == CMD_SIMPLE)
		return (_execute_simple_command(cmd, pipe_in, pipe_out));
	else if (cmd->type == CMD_SUBSHELL)
		return (_execute_subshell(cmd, pipe_in, pipe_out));
	else if (cmd->type == CMD_CONNECTION)
		return (_execute_command_connection(cmd, pipe_in, pipe_out));
	else
	{
		printf("Unsupported Command %d\n", cmd->type);
		exit(EXIT_FAILURE);
	}
}
