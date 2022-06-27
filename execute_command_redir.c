/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:18:12 by jkong             #+#    #+#             */
/*   Updated: 2022/06/28 03:17:05 by jkong            ###   ########.fr       */
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
	char *const	document = heredoc_expand(sh, &redir->word, &length);
	int			here_pipe[2];

	if (pipe(here_pipe) < 0)
		return (-1);
	write_safe(here_pipe[STDOUT_FILENO], document, length);
	free(document);
	close(here_pipe[STDOUT_FILENO]);
	return (here_pipe[STDIN_FILENO]);
}

static int	_redir_open(t_redirect *redir, char *name, t_shell *sh)
{
	int		flags;

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
	return (open(name, flags, 0666));
}

static int	_do_redirection(t_list_redirect *r, char *name, t_shell *sh)
{
	t_redirect *const	redir = &r->redirect;
	int					fd;
	int					res;

	fd = _redir_open(redir, name, sh);
	if (fd < 0)
		return (0);
	res = dup2(fd, redir->redirectee) < 0;
	close(fd);
	if (res < 0)
		return (0);
	return (1);
}

int	do_redirections(t_list_redirect *r_list, t_shell *sh)
{
	int		res;
	char	*name;

	res = 0;
	while (r_list)
	{
		name = redir_expand(sh, &r_list->redirect.word);
		if (!name && r_list->redirect.instruction != R_READING_UNTIL)
		{
			res = -1;
			print_err("%s: ambiguous redirect\n", r_list->redirect.word.str);
		}
		else if (!_do_redirection(r_list, name, sh))
		{
			res = -1;
			print_err("%s: %s\n", name, strerror(errno));
		}
		free(name);
		if (res < 0)
			break ;
		r_list = r_list->next;
	}
	return (res);
}
