/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:35:53 by jkong             #+#    #+#             */
/*   Updated: 2022/06/20 17:40:18 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_vector.h"
#include <unistd.h>

#include <stdio.h>

extern char	**environ;

static void	_execute_simple_command_internal(t_shell *sh, t_simple_command *val,
	int no_fork, int wait)
{
	t_str_vec	*sv;
	t_list_word	*w;
	pid_t		pid;

	if (no_fork)
		pid = 0;
	else
		pid = make_child(sh);
	sh->exit_status = EXIT_SUCCESS;
	if (pid == 0)
	{
		do_redirections(val->redirect_list);
		sv = NULL;
		w = val->word_list;
		if (w)
		{
			while (w)
			{
				sv = strv_append(sv, w->word.str);
				w = w->next;
			}
			execve(val->word_list->word.str, strv_dispose(sv), environ);
		}
		if (!no_fork)
			exit(EXIT_SUCCESS);
	}
	else if (wait)
		sh->exit_status = wait_for(sh, pid);
}

static int	_execute_simple_command(t_shell *sh, t_command *cmd,
	int pipe_in, int pipe_out)
{
	t_simple_command *const	val = cmd->value.simple;
	const int				do_fork = pipe_in != NO_PIPE || pipe_out != NO_PIPE;
	pid_t					pid;

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
	_execute_simple_command_internal(sh, val, do_fork, pipe_out == NO_PIPE);
	if (do_fork)
		exit(sh->exit_status);
	else
		cleanup_redirects(sh);
	return (sh->exit_status);
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
		printf("Unsupported Connector: %d\n", val->connector);
		exit(EXIT_FAILURE);
	}
	return (exec_result);
}

int	execute_command(t_shell *sh, t_command *cmd, int pipe_in, int pipe_out)
{
	if (cmd->type == CMD_SIMPLE)
		return (_execute_simple_command(sh, cmd, pipe_in, pipe_out));
	else if (cmd->type == CMD_SUBSHELL)
		return (_execute_subshell(sh, cmd, pipe_in, pipe_out));
	else if (cmd->type == CMD_CONNECTION)
		return (_execute_command_connection(sh, cmd, pipe_in, pipe_out));
	else
	{
		printf("Unsupported Command %d\n", cmd->type);
		exit(EXIT_FAILURE);
	}
}
