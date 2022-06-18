/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:26:57 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/18 20:59:01 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include "safe_io.h"
#include "libft.h"

void ft_print_error(char *prefix, char *parameter, char *msg)
{
	write_safe(2, prefix, ft_strlen(prefix));
	write_safe(2, parameter, ft_strlen(parameter));
	if (errno != 0)
		strerror(msg);
	else
	{
		write_safe(2, msg, ft_strlen(msg));
		write_safe(2, "\n", 1);
	}
}
