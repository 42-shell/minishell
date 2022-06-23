/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_try_atoi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 05:36:46 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 05:37:10 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

static int	_isspace(int c)
{
	return ((011 <= c && c <= 015) || c == ' ');
}

static int	_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static long	_atol(const char *str)
{
	int		sign;
	long	number;

	while (_isspace(*str))
		str++;
	sign = 0;
	if (*str == '+' || *str == '-')
		sign = *str++ == '-';
	number = 0;
	while (*str && _isdigit(*str))
		number = 10L * number + (1 - (sign << 1)) * (*str++ - '0');
	return (number);
}

static int	_nbrlen(int n)
{
	const int	radix = 10;
	int			count;

	count = n == 0;
	while (n != 0)
	{
		count++;
		n /= radix;
	}
	return (count);
}

int	try_atoi(const char *str, int *out)
{
	int		i;
	int		j;
	long	number;

	if (!out)
		return (0);
	*out = 0;
	i = 0;
	if (*str == '+' || *str == '-')
		i++;
	while (str[i] == '0')
		i++;
	j = 0;
	while (_isdigit(str[i + j]))
		j++;
	if (j > _nbrlen(INT32_MAX) || str[i + j])
		return (0);
	number = _atol(str);
	if (number < INT32_MIN || number > INT32_MAX)
		return (0);
	*out = number;
	return (1);
}
