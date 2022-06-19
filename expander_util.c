/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:54:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/19 22:45:36 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_other_case(\
t_exp_info *info, char *str, t_env_list *env, size_t *ret)
{
	if (*(str + *ret) == '\?')
	{
		info->sb = str_append(info->sb, get_env(env, "EXIT_STATUS"));
	}
	*ret += 1;
}
