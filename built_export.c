/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:36:23 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 07:17:04 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h" // getarr_size , strchr
#include "minishell.h"
#include "string_buffer.h"
#include "string_vector.h"
#include "safe_io.h"

static size_t	export_print_error(int key, char *argv)
{
	if (key == EMPTY_CMD)
		return (print_error("export", "parameter", "empty cmd", 1));
	else if (key == ERROR_OCCURED)
		print_error("export", argv, "not a valid identifier", 1);
	return (-1);
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

static size_t	sort_print_env(t_env_list *env)
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
	clear_env(&cpy);
	return (0);
}

// error_print(export: not an identifier: str)
size_t	ft_export(char **argv, t_env_list *env)
{
	size_t	size;
	size_t	check_error;

	size = length_strvec(argv);
	if (!size)
		return (export_print_error(EMPTY_CMD, NULL));
	else if (size == 1)
		return (sort_print_env(env));
	check_error = 0;
	size = 1;
	while (argv[size])
	{
		if (env_syntax_check(argv[size], SKIP_OFF))
		{
			check_error++;
			export_print_error(ERROR_OCCURED, argv[size]);
		}
		else
			export_work(argv[size], env);
		size++;
	}
	return (check_error > 0);
}
