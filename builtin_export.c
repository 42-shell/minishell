/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:25 by jkong             #+#    #+#             */
/*   Updated: 2022/06/28 02:45:27 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "util_flag.h"
#include "safe_io.h"
#include "string_buffer.h"
#include "string_vector.h"

static t_str_buf	*_append_attributes(t_str_buf *buf, t_var_flags attr)
{
	buf = str_append(buf, "declare -");
	if (has_flag(attr, VF_EXPORTED))
		buf = str_append(buf, "x");
	if (attr == 0)
		buf = str_append(buf, "-");
	return (buf);
}

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
		if (has_flag(it->attr, VF_EXPORTED))
		{
			buf = _append_attributes(buf, it->attr);
			if (it->value)
				buf = str_append_format(buf, " %s=\"%s\"\n", it->name,
						it->value);
			else
				buf = str_append_format(buf, " %s\n", it->name);
		}
		it = it->next;
	}
	str = str_dispose(buf);
	putstr_safe(str);
	free(str);
	dispose_var_list(list);
	return (EXIT_SUCCESS);
}

static void	_append_var(t_list_var **list_ptr, char *name, char *value,
	t_var_flags attr)
{
	t_str_buf	*buf;
	char		*var;

	buf = NULL;
	var = get_var(*list_ptr, name);
	if (var)
		buf = str_append(buf, var);
	buf = str_append(buf, value);
	var = str_dispose(buf);
	put_var(list_ptr, name, var, attr);
	free(var);
}

static int	_set(t_list_var **envp, char *str, size_t idx)
{
	char		*key;
	char		*val;

	if (str[idx] == '\0')
		put_var(envp, str, NULL, VFV_EXPORTED);
	else if (str[idx] == '=')
	{
		key = alloc_str_pair(str, &val, '=');
		put_var(envp, key, val, VFV_EXPORTED);
		free(key);
	}
	else if (str[idx] == '+' && str[idx + 1] == '=')
	{
		key = alloc_str_pair(str, &val, '+');
		*val++ = '\0';
		_append_var(envp, key, val, VFV_EXPORTED);
		free(key);
	}
	else
		return (0);
	return (1);
}

t_builtin_res	ft_export(t_builtin_argv argv, t_builtin_envp envp)
{
	const size_t	argc = length_strvec(argv);
	size_t			i;
	size_t			idx;
	int				err;

	if (argc <= 1)
		return (_show(envp));
	err = 0;
	i = 1;
	while (argv[i])
	{
		idx = 0;
		if (!is_legal_variable(argv[i], &idx) || !_set(envp, argv[i], idx))
		{
			err = 1;
			print_err("export: `%s': not a valid identifier\n", argv[i]);
		}
		i++;
	}
	if (err != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
