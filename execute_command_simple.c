/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_simple.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:35:53 by jkong             #+#    #+#             */
/*   Updated: 2022/06/23 00:32:58 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_vector.h"
#include <unistd.h>

#include <stdio.h>

#include <string.h>
#include "string_buffer.h"

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
		do_redirections(val->redirect_list);
		t_str_vec *sv = NULL;
		t_list_word *w = val->word_list;
		if (w)
		{
			while (w)
			{
				char *str = w->word.str;
				if (strcmp(str, "$?") == 0)
					str = str_dispose(str_append_number(NULL, sh->exit_status));
				sv = strv_append(sv, str);
				w = w->next;
			}
			execve(find_command(sh, val->word_list->word.str), strv_dispose(sv), var_list_to_str_vec(sh->var_list));
		}
		if (!no_fork)
			exit(EXIT_SUCCESS);
	}
	else if (wait)
		status = wait_for(sh, pid);
	return (status);
}
