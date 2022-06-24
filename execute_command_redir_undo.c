/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_redir_undo.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:18:12 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 11:54:18 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_io.h"
#include <unistd.h>

void	add_undo_redirects(t_shell *sh)
{
	int	fd;

	fd = dup(STDIN_FILENO);
	if (fd < 0)
		exit_fail("dup\n");
	sh->redir_undo[0] = fd;
	fd = dup(STDOUT_FILENO);
	if (fd < 0)
		exit_fail("dup\n");
	sh->redir_undo[1] = fd;
	fd = dup(STDERR_FILENO);
	if (fd < 0)
		exit_fail("dup\n");
	sh->redir_undo[2] = fd;
}

void	cleanup_redirects(t_shell *sh)
{
	if (dup2(sh->redir_undo[0], STDIN_FILENO) < 0)
		exit_fail("dup\n");
	close(sh->redir_undo[0]);
	if (dup2(sh->redir_undo[1], STDOUT_FILENO) < 0)
		exit_fail("dup\n");
	close(sh->redir_undo[1]);
	if (dup2(sh->redir_undo[2], STDERR_FILENO) < 0)
		exit_fail("dup\n");
	close(sh->redir_undo[2]);
}
