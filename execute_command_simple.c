/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_simple.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:35:53 by jkong             #+#    #+#             */
/*   Updated: 2022/06/28 16:00:18 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "string_vector.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "builtins.h"

static void	_shell_execve(t_shell *sh, char *file, char **argv)
{
	char	*path;
	char	**envp;

	if (is_absolute_path(file, 1))
		path = resolve_path(NULL, file);
	else
	{
		path = find_path(get_var(sh->var_list, "PATH"), file, FS_PROGRAM, 1);
		if (!path)
		{
			print_err("%s: command not found\n", argv[0]);
			exit(EX_NOTFOUND);
		}
	}
	envp = var_list_to_strvec(sh->var_list, VFV_EXPORTED);
	execve(path, argv, envp);
	free(path);
	free_strvec(envp);
	print_err("%s: %s\n", argv[0], strerror(errno));
	if (errno == ENOENT)
		exit(EX_NOTFOUND);
	else
		exit(EX_NOEXEC);
}

static int	_execute_disk_command(t_shell *sh, char *file, char **argv,
	int flags)
{
	const int	no_fork = flags & 1;
	const int	last_pipe = flags & 2;
	pid_t		pid;

	if (no_fork)
		pid = 0;
	else
		pid = make_child(sh);
	if (pid == 0)
	{
		if (is_absolute_path(file, 1) && file_status(file) == 2)
		{
			print_err("%s: Is a directory\n", argv[0]);
			exit(EX_NOEXEC);
		}
		_shell_execve(sh, file, argv);
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
	argv = word_expand(sh, val->word_list);
	if (length_strvec(argv) <= 0)
		return (EXIT_SUCCESS);
	status = EXIT_SUCCESS;
	cmd = argv[0];
	builtin = get_builtin(cmd);
	if (builtin)
		status = builtin(argv, &sh->var_list);
	else
		status = _execute_disk_command(sh, cmd, argv, flags);
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
