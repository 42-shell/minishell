/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:47:54 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 15:16:08 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "env_module.h"

size_t	ft_env(char **argv, t_env_list *head)
{
	if (ft_getarr_size(argv) != 1)
		return (-1);
	return (print_env(head));
}
