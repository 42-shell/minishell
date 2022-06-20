/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:35:53 by jkong             #+#    #+#             */
/*   Updated: 2022/06/20 21:56:10 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_vector.h"
#include <unistd.h>

#include <stdio.h>

extern char	**environ;

#include <string.h>
#include "string_buffer.h"

static int	_execute_simple_command_internal(t_shell *sh, t_simple_command *val,
	int no_fork, int wait)
{
	t_str_vec	*sv;
	t_list_word	*w;
	pid_t		pid;
	int			status;

	if (no_fork)
		pid = 0;
	else
		pid = make_child(sh);
	status = EXIT_SUCCESS;
	if (pid == 0)
	{
		do_redirections(val->redirect_list);
		sv = NULL;
		w = val->word_list;
		if (w)
		{
			while (w)
			{
				char *str = w->word.str;
				if (strcmp(str, "$?") == 0)
				{
					t_str_buf *sb = NULL;
					int n = sh->exit_status;
					const int		sign = n < 0;
					char			buf[11];
					const size_t	count = sizeof(buf) / sizeof(*buf);
					size_t			i;

					i = count;
					if (!n)
						buf[--i] = '0';
					while (n)
					{
						buf[--i] = '0' + (1 - (sign << 1)) * (n % 10);
						n /= 10;
					}
					if (sign)
						buf[--i] = '-';
					sb = str_append_raw(sb, buf + i, count - i);
					str = str_dispose(sb);
				}
				sv = strv_append(sv, str);
				w = w->next;
			}
			execve(val->word_list->word.str, strv_dispose(sv), environ);
		}
		if (!no_fork)
			exit(EXIT_SUCCESS);
	}
	else if (wait)
		status = wait_for(sh, pid);
	return (status);
}

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
	exec_result = _execute_simple_command_internal(sh, cmd->value.simple,
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
		printf("Unsupported Connector: %d\n", val->connector);
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
		printf("Unsupported Command %d\n", cmd->type);
		exit(EXIT_FAILURE);
	}
	if (pipe_out == NO_PIPE)
		sh->exit_status = exec_result;
	return (exec_result);
}
