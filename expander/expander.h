/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:46:57 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/16 13:33:09 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "env_module.h"

enum e_exp_type
{
	PASS = 0,
	D_QUOTE,
	S_QUOTE,
	ENV,
	WILDCARD,
};

typedef struct s_exp_check
{
	int			flag;
}				t_exp_check;

typedef struct s_exp_info
{
	char		**exp_output;
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
int		create_expand_arr(t_exp_info *info, char *cpy_target, int idx);
void	ft_free_exp_info(t_exp_info *info);

#endif
