/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:34:05 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 19:50:32 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "libft.h"
#include "safe_io.h"
#include "safe_mem.h"

extern char		**environ;
sig_atomic_t	g_exit_status;

static void	_eval(t_shell *sh, t_parser *pst, char *rl)
{
	pst->str = rl;
	pst->begin = pst->str;
	pst->error = PE_SUCCESS;
	if (parse(pst) & (gather_here_document(pst) == 0))
	{
		sh->next_pipe = NO_PIPE;
		g_exit_status = execute_command(sh, &pst->now->command,
				NO_PIPE, NO_PIPE);
		add_history(rl);
	}
	else
		g_exit_status = EX_BADUSAGE;
	parser_stack_remove_all(pst);
}

static void	_reader_loop(t_shell *sh, t_parser *pst)
{
	char	*rl;

	set_signal_handler(1);
	while (1)
	{
		rl = readline("$ ");
		if (!rl)
		{
			puterr_safe("exit\n");
			break ;
		}
		if (ft_strlen(rl) != 0)
			_eval(sh, pst, rl);
		free(rl);
	}
}

int	main(int argc, char *argv[])
{
	t_shell		sh;
	t_parser	pst;

	(void)&argc;
	(void)&argv;
	ft_memset(&sh, 0, sizeof(sh));
	ft_memset(&pst, 0, sizeof(pst));
	parser_stack_reserve(&pst, 1);
	sh.var_list = strvec_to_var_list(environ);
	_reader_loop(&sh, &pst);
	free(pst.stack_base);
	dispose_var_list(sh.var_list);
	return (g_exit_status);
}

char	*get_ifs(t_list_var *v_list)
{
	char *const	value = get_var(v_list, "IFS", 0);

	if (ft_strlen(value) == 0)
		return (" \t\n");
	return (value);
}
