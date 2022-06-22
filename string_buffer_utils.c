/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_buffer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:37:07 by jkong             #+#    #+#             */
/*   Updated: 2022/06/22 14:50:29 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_buffer.h"

t_str_buf	*str_append_number(t_str_buf *buf, int n)
{
	const int		sign = n < 0;
	char			arr[11];
	const size_t	count = sizeof(arr) / sizeof(*arr);
	size_t			i;

	i = count;
	if (!n)
		arr[--i] = '0';
	while (n)
	{
		arr[--i] = '0' + (1 - (sign << 1)) * (n % 10);
		n /= 10;
	}
	if (sign)
		arr[--i] = '-';
	return (str_append_raw(buf, arr + i, count - i));
}
