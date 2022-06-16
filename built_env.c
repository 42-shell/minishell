/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:47:54 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/16 11:28:16 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h" //getarr_size

size_t	ft_env(char **argv, t_env_list *head)
{
	if (ft_getarr_size(argv) != 1)
		return (-1);
	print_env(head, NON_VISIBLE);
	return (0);
}
