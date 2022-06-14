/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:46:57 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/14 15:47:03 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "env_module.h"

enum e_exp_type
{
	double_quote	= 2;
	single_quote	= 4;
	dollar			= 8;
	asterisk		= 16;
	pass			= 32;
}

typedef s_struct	s_exp_check
{
	int			flag;
}				t_exp_check;

typedef s_struct	s_exp_info
{
	char		**exp_arr;
	size_t		malloc_size;
	size_t		cur_src_pos;
	size_t		cur_pos;
	t_exp_check	check;
}				t_exp_info;

/*
** main_function
*/
char	**check_expand(char **argv, t_env_list *head);


/*
** util_function
*/
int		create_expand_arr(t_expand_info *info, char *cpy_target, int idx);
void	ft_free_exp_info(t_exp_info *info);

#endif
