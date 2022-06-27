/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 19:01:17 by jkong             #+#    #+#             */
/*   Updated: 2022/06/28 02:39:19 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_buffer.h"
#include "safe_io.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>

static void	_write_document_pipe_internal(int fildes[2], char *eof, t_shell *sh)
{
	char	*str;

	set_signal_handler(2);
	close(fildes[STDIN_FILENO]);
	str = read_document(eof, sh);
	write_safe(fildes[STDOUT_FILENO], str, ft_strlen(str));
	free(str);
	close(fildes[STDOUT_FILENO]);
}

static char	*_read_document_pipe_internal(int fd, char *str, size_t len)
{
	t_str_buf	*buf;
	ssize_t		size;

	buf = NULL;
	while (1)
	{
		size = read(fd, str, len);
		if (size < 0)
		{
			free(str_dispose(buf));
			return (NULL);
		}
		else if (size == 0)
			break ;
		buf = str_append_raw(buf, str, size);
	}
	return (str_dispose(buf));
}

static char	*_wait_document_pipe_internal(int fildes[2], pid_t pid)
{
	const size_t	len = GROW_THRESHOLD;
	char			*buf;
	char			*str;
	int				status;
	pid_t			got_pid;

	set_signal_handler(0);
	close(fildes[STDOUT_FILENO]);
	buf = malloc_safe(len);
	str = _read_document_pipe_internal(fildes[STDIN_FILENO], buf, len);
	close(fildes[STDIN_FILENO]);
	free(buf);
	got_pid = waitpid(pid, &status, 0);
	if (got_pid < 0)
		exit_fail("waitpid");
	if (WIFSIGNALED(status))
		on_signal();
	set_signal_handler(1);
	g_exit_status = get_exit_status(status);
	return (str);
}

char	*read_document_pipe(char *eof, t_shell *sh)
{
	int			fildes[2];
	pid_t		pid;

	if (pipe(fildes) < 0)
		exit_fail("pipe error");
	pid = fork();
	if (pid < 0)
		exit_fail("fork");
	else if (pid == 0)
	{
		_write_document_pipe_internal(fildes, eof, sh);
		exit(EXIT_SUCCESS);
	}
	return (_wait_document_pipe_internal(fildes, pid));
}
