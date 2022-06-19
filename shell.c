/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:34:05 by jkong             #+#    #+#             */
/*   Updated: 2022/06/20 02:21:41 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "libft.h"
#include "safe_mem.h"

void	__todo_stack_capacity(t_parser *pst)
{
	size_t	capacity;

	capacity = 200;
	pst->stack_capacity = capacity;
	pst->stack_base = calloc_safe(capacity, sizeof(*pst->stack_base));
	pst->now = pst->stack_base;
}

void	__todo_stack_destroy(t_parser *pst)
{
	while (pst->now > pst->stack_base)
		clear_parser_stack_item(pst->now--);
}

int	main(int argc, char *argv[])
{
	t_shell		sh;
	t_parser	pst;
	char		*rl;
	int			exit_status;

	(void)&argc;
	(void)&argv;
	exit_status = 0;
	ft_memset(&sh, 0, sizeof(sh));
	ft_memset(&pst, 0, sizeof(pst));
	__todo_stack_capacity(&pst);
	while (1)
	{
		rl = readline("$ ");
		if (!rl)
		{
			printf("exit\n");
			break ;
		}
		pst.str = rl;
		pst.begin = pst.str;
		pst.error = PE_SUCCESS;
		if (parse(&pst))
		{
			sh.exit_status = -1;
			gather_here_document(&pst);
			execute_command(&sh, &pst.now->command, NO_PIPE, NO_PIPE);
			add_history(rl);
		}
		__todo_stack_destroy(&pst);
		free(rl);
	}
	free(pst.stack_base);
	return (exit_status);
}
