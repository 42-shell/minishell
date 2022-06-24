/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:25 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 11:37:12 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "util_flag.h"
#include "safe_io.h"
#include "string_buffer.h"
#include "string_vector.h"

static int	_show(t_list_var **envp)
{
	t_list_var *const	list = sort_var_list(clone_var_list(*envp));
	t_list_var			*it;
	t_str_buf			*buf;
	char				*str;

	buf = NULL;
	it = list;
	while (it)
	{
		buf = str_append(buf, "declare -");
		if (has_flag(it->attr, VF_EXPORTED))
			buf = str_append(buf, "x");
		if (it->attr == 0)
			buf = str_append(buf, "-");
		if (it->value)
			buf = str_append_format(buf, " %s=\"%s\"\n", it->name, it->value);
		else
			buf = str_append_format(buf, " %s\n", it->name);
		it = it->next;
	}
	str = str_dispose(buf);
	putstr_safe(str);
	free(str);
	dispose_var_list(list);
	return (EXIT_SUCCESS);
}

static int	_legal_variable_name(char *name, char delim)
{
	size_t	i;

	i = 0;
	if (legal_variable_starter(name[i++]))
	{
		while (legal_variable_char(name[i]))
			i++;
		if (name[i] == delim)
			return (1);
	}
	return (0);
}

static void	_set(t_list_var **envp, char *str)
{
	char	*key;
	char	*val;
	int		attr;

	attr = 0;
	set_flag(&attr, VF_EXPORTED);
	key = alloc_str_pair(str, &val, '=');
	put_var(envp, key, val, attr);
	free(key);
}

static void	_set_null(t_list_var **envp, char *key)
{
	int		attr;

	attr = 0;
	set_flag(&attr, VF_EXPORTED);
	put_var(envp, key, NULL, attr);
}

t_builtin_res	ft_export(t_builtin_argv argv, t_builtin_envp envp)
{
	const size_t	argc = length_strvec(argv);
	size_t			i;
	int				err;

	if (argc <= 1)
		return (_show(envp));
	err = 0;
	i = 1;
	while (argv[i])
	{
		if (_legal_variable_name(argv[i], '='))
			_set(envp, argv[i]);
		else if (_legal_variable_name(argv[i], '\0'))
			_set_null(envp, argv[i]);
		else
		{
			err |= 1;
			print_err("export: not an identifier: %s\n", argv[i]);
		}
		i++;
	}
	if (err == 0)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
