/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:35:53 by jkong             #+#    #+#             */
/*   Updated: 2022/06/16 18:47:52 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

static void	_execute_command_internal(t_command *cmd);

void	execute_command(t_command *cmd)
{
	_execute_command_internal(cmd);
}

static void	_execute_simple_command(t_simple_command *cmd)
{
	(void)&cmd;
	if (cmd->word_list)
		printf("SimpleCommand %s\n", cmd->word_list->word.str);
	else
		printf("NullCommand\n");
}

static void	_execute_subshell(t_subshell_command *cmd)
{
	(void)&cmd;
	printf("Subshell (\n");
	_execute_command_internal(&cmd->container);
	printf(")\n");
}

static void	_execute_command_connection(t_command_connection *cmd)
{
	(void)&cmd;
	printf("Connection {\n");
	_execute_command_internal(&cmd->first);
	printf("  %c [ %d ]\n", cmd->connector, cmd->connector);
	_execute_command_internal(&cmd->second);
	printf("}\n");
}

static void	_execute_command_internal(t_command *cmd)
{
	if (cmd->type == CMD_SIMPLE)
		_execute_simple_command(cmd->value.simple);
	else if (cmd->type == CMD_SUBSHELL)
		_execute_subshell(cmd->value.subshell);
	else if (cmd->type == CMD_CONNECTION)
		_execute_command_connection(cmd->value.connection);
}
