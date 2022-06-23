/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_simple.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:35:53 by jkong             #+#    #+#             */
/*   Updated: 2022/06/23 20:37:36 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_vector.h"
#include <unistd.h>

int	execute_simple_command_internal(t_shell *sh, t_simple_command *val,
	int no_fork, int wait)
{
	pid_t		pid;
	int			status;

	if (no_fork)
		pid = 0;
	else
		pid = make_child(sh);
	status = EXIT_SUCCESS;
	if (pid == 0)
	{
		//find_builtin
		if (do_redirections(val->redirect_list, sh) < 0)
			status = EXIT_FAILURE;
		if (status == EXIT_SUCCESS && val->word_list)
			//if execve fails
			execve(find_command(sh, val->word_list->word.str),
				strv_dispose(expand_list(NULL, sh, val->word_list, 1)),
				var_list_to_strvec(sh->var_list));
		if (!no_fork)
			exit(status);
	}
	else if (wait)
		status = wait_for(sh, pid);
	return (status);
}
