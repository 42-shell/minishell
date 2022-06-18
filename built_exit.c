/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:42:44 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/18 22:21:27 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"
#include "safe_io.h"
#include "minishell.h"

static int	is_all_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		str++;
	}
	return (0);
}

static int	atoi_done_exit(char **argv, size_t size)
{
	size_t	atoi;

	if (size > 2)
	{
		putstr_safe("exit\n");
		return (print_error("exit", NULL, "too many arguments"));
	}
	else
	{
		atoi = ft_atoi(argv[1]);
		putstr_safe("exit\n");
		return (atoi & 255);
	}
}

int	ft_exit(char **argv)
{
	size_t	size;
	size_t	atoi;

	size = ft_getarr_size(argv);
	if (!size)
		return (print_error("exit", NULL, "empty arg_vector"));
	else if (size == 1)
	{
		putstr_safe("exit\n");
		return (0);
	}
	else
	{
		if (!is_all_digit(argv[1]))
		{
			return (atoi_done_exit(argv, size));
		}
		else
		{
			putstr_safe("exit\n");
			print_error("exit", argv[1], "numeric argument required");
			return (255);
		}
	}
}
