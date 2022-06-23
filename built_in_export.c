/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:36:23 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/23 13:39:10 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h" // getarr_size , strchr
#include "minishell.h"
#include "string_buffer.h"
#include "string_vector.h"
#include "safe_io.h"
#include "generic_list.h"
#include <stdlib.h>

// asd

static void	export_work(char *id, t_env_list *env)
{
	char		*pos;

	pos = ft_strchr(id, '=');
	if (pos)
		id[pos - id] = '\0';
	if (get_env(env, id))
	{
		if (pos)
			change_env(env, id, &id[pos - id + 1]);
		else
			change_env(env, id, "");
	}
	else
	{
		if (pos)
			ft_lstnew(id, &id[pos - id + 1], &env, ON_VISIBLE);
		else
			ft_lstnew(id, "", &env, NON_VISIBLE);
	}
}

static int	_clear_env(t_env_list *ptr)
{
	if (ptr)
	{
		free(ptr->id);
		free(ptr->content);
		free(ptr);
	}
	return (0);
}

static int	sort_print_env(t_env_list *env)
{
	t_env_list	*cpy;

	cpy = NULL;
	while (env)
	{
		if (ft_strcmp(env->id, "_"))
			ft_lstcpy(env, &cpy);
		env = env->next;
	}
	print_env(cpy, ON_VISIBLE);
	list_walk((void *)&cpy, _clear_env);
	return (0);
}

// error_print(export: not an identifier: str)
int	ft_export(char **argv, t_env_list **env)
{
	size_t	size;
	size_t	check_error;

	size = length_strvec(argv);
	if (size == 1)
		return (sort_print_env(*env));
	check_error = 0;
	size = 1;
	while (argv[size])
	{
		if (env_syntax_check(argv[size], 0))
		{
			check_error++;
			built_in_print_error("export", argv[size], "not a valid identifier");
			//return (EXIT_FAILURE); // Save to last command exit status
		}
		else
			export_work(argv[size], *env);
		size++;
	}
	return (check_error > 0);
}
