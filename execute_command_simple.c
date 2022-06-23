/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_simple.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:35:53 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 00:36:10 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_vector.h"
#include <unistd.h>
#include "builtins.h"

static int	_execute_disk_command(t_shell *sh, char *file, char **argv,
	int flags)
{
	const int	no_fork = flags & 1;
	const int	last_pipe = flags & 2;
	pid_t		pid;
	int			exec_res;

	if (no_fork)
		pid = 0;
	else
		pid = make_child(sh);
	if (pid == 0)
	{
		exec_res = execve(file, argv, var_list_to_strvec(sh->var_list));
		//exec 실패?!
		exit(EXIT_FAILURE);
	}
	else if (last_pipe)
		return (wait_for(sh, pid));
	return (EXIT_SUCCESS);
}

static int	_execute_simple_command_internal(t_shell *sh, t_simple_command *val,
	int flags)
{
	char			**argv;
	int				status;
	char			*cmd;
	t_builtin_func	builtin;

	if (do_redirections(val->redirect_list, sh) < 0)
		return (EXIT_FAILURE);
	if (!val->word_list)
		return (EXIT_SUCCESS);
	argv = strv_dispose(expand_list(NULL, sh, val->word_list, 1));
	status = EXIT_SUCCESS;
	cmd = argv[0];
	builtin = get_builtin(cmd);
	if (builtin)
		status = (builtin(argv, &sh->var_list));
	else
	{
		cmd = find_command(sh, cmd);
		status = _execute_disk_command(sh, cmd, argv, flags);
		free(cmd);
	}
	free_strvec(argv);
	return (status);
}

int	execute_simple_command(t_shell *sh, t_command *cmd,
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
			(!!do_fork << 0) | ((pipe_out == NO_PIPE) << 1));
	if (do_fork)
		exit(exec_result);
	else
		cleanup_redirects(sh);
	return (exec_result);
}
