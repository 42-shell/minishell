/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:18:12 by jkong             #+#    #+#             */
/*   Updated: 2022/06/19 04:02:41 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_io.h"
#include "generic_list.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char	*__todo_redirection_expand(t_word *word);
char	*__todo_heredoc_expand(t_word *word, size_t *len_ptr);

static int	_redir_open(t_redirect *redir, int flags)
{
	size_t		length;
	char *const	document = __todo_heredoc_expand(&redir->word, &length);
	int			here_pipe[2];

	if (flags)
		return (open(__todo_redirection_expand(&redir->word), flags, 0666));
	//length == 0 -> /dev/null O_RDONLY
	//length > HEREDOC_PIPESIZE -> MAKE TEMPORARY FILE
	//otherwise -> herepipe
	if (pipe(here_pipe) < 0)
		return (-1);
	write_safe(here_pipe[STDOUT_FILENO], document, length);
	free(document);
	close(here_pipe[STDOUT_FILENO]);
	return (here_pipe[STDIN_FILENO]);
}

static int	_do_redirection(t_list_redirect *r)
{
	t_redirect *const	redir = &r->redirect;
	int					flags;
	int					fd;

	if (redir->instruction == R_OUTPUT_DIRECTION)
		flags = O_TRUNC | O_WRONLY | O_CREAT;
	else if (redir->instruction == R_INPUT_DIRECTION)
		flags = O_RDONLY;
	else if (redir->instruction == R_APPENDING_TO)
		flags = O_APPEND | O_WRONLY | O_CREAT;
	else if (redir->instruction == R_OUTPUT_DIRECTION)
		flags = 0;
	else
	{
		printf("Unsupported redirect instruction %d\n", redir->instruction);
		exit(EXIT_FAILURE);
	}
	fd = _redir_open(redir, flags);
	if (fd < 0)
		return (-1);
	if (dup2(fd, redir->redirectee) < 0)
		return (-2);
	return (0);
}

int	do_redirections(t_list_redirect *r_list)
{
	return (list_walk((void *)r_list, _do_redirection));
}

void	add_undo_redirects(int undo[3])
{
	int	fd;

	fd = dup(STDIN_FILENO);
	if (fd < 0)
	{
		puterr_safe("dup\n");
		exit(EXIT_FAILURE);
	}
	undo[0] = fd;
	fd = dup(STDOUT_FILENO);
	if (fd < 0)
	{
		puterr_safe("dup\n");
		exit(EXIT_FAILURE);
	}
	undo[1] = fd;
	fd = dup(STDERR_FILENO);
	if (fd < 0)
	{
		puterr_safe("dup\n");
		exit(EXIT_FAILURE);
	}
	undo[2] = fd;
}

void	cleanup_redirects(int undo[3])
{
	if (dup2(undo[0], STDIN_FILENO) < 0)
	{
		puterr_safe("dup\n");
		exit(EXIT_FAILURE);
	}
	close(undo[0]);
	if (dup2(undo[1], STDOUT_FILENO) < 0)
	{
		puterr_safe("dup\n");
		exit(EXIT_FAILURE);
	}
	close(undo[1]);
	if (dup2(undo[2], STDERR_FILENO) < 0)
	{
		puterr_safe("dup\n");
		exit(EXIT_FAILURE);
	}
	close(undo[2]);
}
