/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:51:56 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 16:13:30 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	set_flag(int *ptr, int index)
{
	*ptr |= 1 << index;
}

void	reset_flag(int *ptr, int index)
{
	*ptr = ~(1 << index);
}

int	has_flag(int flags, int index)
{
	return ((flags >> index) & 1);
}

int	add_flag(int flags, int index)
{
	return (flags | (1 << index));
}

int	remove_flag(int flags, int index)
{
	return (flags & ~(1 << index));
}
