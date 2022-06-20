/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 21:31:58 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 15:58:31 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"
#include "string_buffer.h"
#include "safe_io.h"

static size_t	echo_print_error(int key, t_env_list *env)
{
	if (key == EMPTY_CMD)
		return (print_error("echo", "parameter", "empty cmd", 1));
	else
		return (-1);
}

static size_t	check_option_parameter(char **argv)
{
	size_t	idx;
	size_t	pos;

	idx = 1;
	while (argv[idx])
	{
		pos = 1;
		if (argv[idx][0] == '-')
		{
			while (argv[idx][pos] == 'n')
				pos++;
			if (argv[idx][pos] != '\0')
				return (idx - 1);
		}
		else
			return (idx - 1);
		idx++;
	}
	return (idx - 1);
}

static void	echo_workhorse(t_str_buf *sb, char **argv, size_t idx, size_t opt)
{	
	char	*temp;

	while (argv[idx])
	{
		sb = str_append(sb, argv[idx]);
		if (argv[idx + 1])
			sb = str_append(sb, " ");
		idx++;
	}
	if (opt == 1)
		sb = str_append(sb, "\n");
	temp = str_dispose(sb);
	if (temp)
	{
		putstr_safe(temp);
		free(temp);
	}
}

size_t	ft_echo(char **argv, t_env_list *env)
{
	size_t		opt_pos;
	t_str_buf	*sb;

	if (!ft_getarr_size(argv))
		return (echo_print_error(EMPTY_CMD, env));
	sb = NULL;
	opt_pos = check_option_parameter(argv);
	opt_pos++;
	echo_workhorse(sb, argv, opt_pos, opt_pos);
	return (0);
}
