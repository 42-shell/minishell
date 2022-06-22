/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:18:12 by jkong             #+#    #+#             */
/*   Updated: 2022/06/22 22:24:53 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_io.h"
#include "generic_list.h"
#include <fcntl.h>
#include <unistd.h>

char	*__todo_redirection_expand(t_word *word);
char	*__todo_heredoc_expand(t_word *word, size_t *len_ptr);

// length == 0 -> /dev/null O_RDONLY
// length > HEREDOC_PIPESIZE -> MAKE TEMPORARY FILE
// otherwise -> herepipe
static int	_document_fd(t_redirect *redir)
{
	size_t		length;
	char *const	document = __todo_heredoc_expand(&redir->word, &length);
	int			here_pipe[2];

	if (pipe(here_pipe) < 0)
		return (-1);
	write_safe(here_pipe[STDOUT_FILENO], document, length);
	free(document);
	close(here_pipe[STDOUT_FILENO]);
	return (here_pipe[STDIN_FILENO]);
}

static int	_redir_open(t_redirect *redir)
{
	int	flags;

	if (redir->instruction == R_OUTPUT_DIRECTION)
		flags = O_TRUNC | O_WRONLY | O_CREAT;
	else if (redir->instruction == R_INPUT_DIRECTION)
		flags = O_RDONLY;
	else if (redir->instruction == R_APPENDING_TO)
		flags = O_APPEND | O_WRONLY | O_CREAT;
	else if (redir->instruction == R_READING_UNTIL)
		return (_document_fd(redir));
	else
	{
		print_err("Unsupported redirect instruction %d\n", redir->instruction);
		exit(EXIT_FAILURE);
	}
	return (open(__todo_redirection_expand(&redir->word), flags, 0666));
}

static int	_do_redirection(t_list_redirect *r)
{
	t_redirect *const	redir = &r->redirect;
	int					fd;
	int					res;

	fd = _redir_open(redir);
	if (fd < 0)
		return (-1);
	res = dup2(fd, redir->redirectee) < 0;
	close(fd);
	if (res < 0)
		return (-2);
	return (0);
}

int	do_redirections(t_list_redirect *r_list)
{
	int	res;

	res = list_walk((void *)r_list, _do_redirection);
	if (res < 0)
	{
		print_err("Redirection failure %d\n", res);
		exit(EXIT_FAILURE);
	}
	return (res);
}
