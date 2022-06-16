/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:34:05 by jkong             #+#    #+#             */
/*   Updated: 2022/06/16 18:29:10 by jkong            ###   ########.fr       */
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
}

int	main(int argc, char *argv[])
{
	t_parser	pst;
	char		*rl;
	int			exit_status;

	(void)&argc;
	(void)&argv;
	exit_status = 0;
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
		pst.now = pst.stack_base;
		parse(&pst);
		gather_here_document(&pst);
		execute_command(&pst.now->command);
		dispose_command_recursive(&pst.now->command);
		add_history(rl);
		free(rl);
	}
	free(pst.stack_base); //__todo
	return (exit_status);
}
