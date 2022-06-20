/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 21:31:58 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 08:12:02 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "string_buffer.h"
#include "string_vector.h"
#include "safe_io.h"

static int	echo_print_error(int key)
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

int	ft_echo(char **argv, t_env_list **env)
{
	size_t		opt_pos;
	t_str_buf	*sb;

	(void)env;
	if (!length_strvec(argv))
		return (echo_print_error(EMPTY_CMD));
	sb = NULL;
	opt_pos = check_option_parameter(argv);
	opt_pos++;
	echo_workhorse(sb, argv, opt_pos, opt_pos);
	return (0);
}
