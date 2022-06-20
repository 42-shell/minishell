/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:54:30 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 18:27:46 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// exit_status should change to mini_info
void	expand_other_case(\
t_exp_info *info, char *str, t_env_list *env, size_t *ret)
{
	if (*(str + *ret) == '\0')
		info->sb = str_append_raw(info->sb, "$", 1);
	else if (*(str + *ret) == '\?')
	{
		info->sb = str_append(info->sb, get_env(env, "EXIT_STATUS"));
		*ret += 1;
	}
	else
		*ret += 1;
}
