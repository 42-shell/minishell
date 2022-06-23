/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:18:12 by jkong             #+#    #+#             */
/*   Updated: 2022/06/23 20:34:45 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_io.h"
#include "generic_list.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// length == 0 -> /dev/null O_RDONLY
// length > HEREDOC_PIPESIZE -> MAKE TEMPORARY FILE
// otherwise -> herepipe
static int	_document_fd(t_redirect *redir, t_shell *sh)
{
	size_t		length;
	char *const	document = expand_heredoc(sh, &redir->word, &length);
	int			here_pipe[2];

	if (pipe(here_pipe) < 0)
		return (-1);
	write_safe(here_pipe[STDOUT_FILENO], document, length);
	free(document);
	close(here_pipe[STDOUT_FILENO]);
	return (here_pipe[STDIN_FILENO]);
}

static int	_redir_open(t_redirect *redir, t_shell *sh, int *err)
{
	int		flags;
	char	*name;
	int		fd;

	if (redir->instruction == R_OUTPUT_DIRECTION)
		flags = O_TRUNC | O_WRONLY | O_CREAT;
	else if (redir->instruction == R_INPUT_DIRECTION)
		flags = O_RDONLY;
	else if (redir->instruction == R_APPENDING_TO)
		flags = O_APPEND | O_WRONLY | O_CREAT;
	else if (redir->instruction == R_READING_UNTIL)
		return (_document_fd(redir, sh));
	else
	{
		print_err("Unsupported redirect instruction %d\n", redir->instruction);
		exit(EXIT_FAILURE);
	}
	name = expand_redir(sh, &redir->word, 1);
	fd = -1;
	if (name)
		fd = open(name, flags, 0666);
	else
		*err = -2;
	free(name);
	return (fd);
}

static int	_do_redirection(t_list_redirect *r, t_shell *sh)
{
	t_redirect *const	redir = &r->redirect;
	int					fd;
	int					res;
	int					err;

	err = -1;
	fd = _redir_open(redir, sh, &err);
	if (fd < 0)
		return (err);
	res = dup2(fd, redir->redirectee) < 0;
	close(fd);
	if (res < 0)
		return (-1);
	return (0);
}

int	do_redirections(t_list_redirect *r_list, t_shell *sh)
{
	int		res;
	char	*name;

	res = 0;
	while (r_list)
	{
		res = _do_redirection(r_list, sh);
		if (res < 0)
		{
			name = r_list->redirect.word.str;
			if (res == -1)
				print_err("%s: %s\n", name, strerror(errno));
			else if (res == -2)
				print_err("%s: ambiguous redirect\n", name);
			break ;
		}
		r_list = r_list->next;
	}
	return (res);
}
