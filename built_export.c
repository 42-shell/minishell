/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:36:23 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/19 03:32:22 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h" // getarr_size , strchr
#include "minishell.h"
#include "string_buffer.h"
#include "safe_io.h"

static size_t	export_print_error(int key, char *argv, t_env_list *env)
{
	if (key == EMPTY_CMD)
	{
		change_env(env, "EXIT_STATUS", "1");
		return (print_error("export", "parameter", "empty cmd"));
	}
	else if (key == ERROR_OCCURED)
	{
		print_error("export", argv, "not a valid identifier");
	}
	return (-1);
}

static size_t	export_check_error(t_env_list *env, size_t check_error)
{
	change_late_cmd(env, "export", BUILT_IN);
	if (check_error)
	{
		change_env(env, "EXIT_STATUS", "1");
		return (-1);
	}
	else
	{
		change_env(env, "EXIT_STATUS", "0");
		return (0);
	}
}

static size_t	sort_print_env(t_env_list *env)
{
	t_env_list	*cpy;

	cpy = NULL;
	while (env)
	{
		ft_lstcpy(env, &cpy);
		env = env->next;
	}
	print_env(cpy, ON_VISIBLE);
	clear_env(&cpy);
	change_env(env, "EXIT_STATUS", "0");
	return (0);
}

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

// error_print(export: not an identifier: str)
size_t	ft_export(char **argv, t_env_list *env)
{
	size_t	size;
	size_t	check_error;

	change_late_cmd(env, "export", BUILT_IN);
	size = ft_getarr_size(argv);
	if (!size)
		return (export_print_error(EMPTY_CMD, NULL, env));
	if (size == 1)
		return (sort_print_env(env));
	check_error = 0;
	size = 1;
	while (argv[size])
	{	
		if (env_syntax_check(argv[size], SKIP_OFF))
		{
			check_error++;
			export_print_error(ERROR_OCCURED, argv[size], env);
		}
		else
			export_work(argv[size], env);
		size++;
	}
	return (export_check_error(env, check_error));
}
