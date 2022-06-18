/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string_to_integer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:53:11 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/18 21:00:08 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static int	_isspace(int c)
{
	return ((011 <= c && c <= 015) || c == ' ');
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	number;

	while (_isspace(*str))
		str++;
	sign = 0;
	if (*str == '+' || *str == '-')
		sign = *str++ == '-';
	number = 0;
	while (*str && ft_isdigit(*str))
		number = 10 * number + (1 - (sign << 1)) * (*str++ - '0');
	return (number);
}
