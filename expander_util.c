/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:54:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/18 20:18:09 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_find_exit_status(t_exp_info *info, t_env_list *env, size_t *ret)
{
	*ret += 1;
	info->sb = str_append(info->sb, get_env(env, "EXIT_STATUS"));
}
