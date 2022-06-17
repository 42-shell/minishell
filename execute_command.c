/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:35:53 by jkong             #+#    #+#             */
/*   Updated: 2022/06/17 19:04:30 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

#include <stdio.h>

extern char	**environ;

static void	_execute_simple_command(t_command *cmd, int pipe_in, int pipe_out)
{
	t_simple_command *const	val = cmd->value.simple;

	(void)pipe_in;
	(void)pipe_out;
	if (val->word_list)
		printf("SimpleCommand[%d, %d] %s\n", pipe_in, pipe_out, val->word_list->word.str);
	else
		printf("NullCommand\n");
}

static void	_execute_subshell(t_command *cmd, int pipe_in, int pipe_out)
{
	t_subshell_command *const	val = cmd->value.subshell;

	(void)pipe_in;
	(void)pipe_out;
	printf("Subshell (\n");
	execute_command(&val->container, pipe_in, pipe_out);
	printf(")\n");
}

void	execute_pipeline(t_command *cmd, int pipe_in, int pipe_out);

static void	_execute_command_connection(t_command *cmd, int pipe_in,
	int pipe_out)
{
	t_command_connection *const	val = cmd->value.connection;

	(void)pipe_in;
	(void)pipe_out;
	if (val->connector == TK_OR)
	{
		execute_pipeline(cmd, pipe_in, pipe_out);
	}
	else
	{
		printf("Connection {\n");
		execute_command(&val->first, pipe_in, pipe_out);
		printf("  %c [ %d ]\n", val->connector, val->connector);
		execute_command(&val->second, pipe_in, pipe_out);
		printf("}\n");
	}
}

void	execute_command(t_command *cmd, int pipe_in, int pipe_out)
{
	if (cmd->type == CMD_SIMPLE)
		_execute_simple_command(cmd, pipe_in, pipe_out);
	else if (cmd->type == CMD_SUBSHELL)
		_execute_subshell(cmd, pipe_in, pipe_out);
	else if (cmd->type == CMD_CONNECTION)
		_execute_command_connection(cmd, pipe_in, pipe_out);
}
