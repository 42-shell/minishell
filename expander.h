/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:46:57 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 15:11:48 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "env_module.h"
# include "libft.h"
# include "string_buffer.h"
# include "string_vector.h"
# include "minishell.h"
# include "util_flag.h"
# include "glob.h"

# define SOH 1

enum	e_sub_flag
{
	EXP_DEQUO = 0,
	EXP_SUBST = 1,
	EXP_PASS = 2,
};

typedef struct s_exp_info
{
	size_t		cur_pos;
	char		**temp;
	t_str_buf	*sb;
	t_str_buf	*sb_dollar;
	t_str_vec	*sv;
	int			last_exit_status;
}				t_exp_info;

/*
** main_function
*/
char	**check_expand(t_shell *sh, char **argv, t_env_list *env);

size_t	_dollar(t_exp_info *info, t_env_list *env, char *str);
size_t	_s_quote(t_exp_info *info, char *str, int key);
size_t	_d_quote(t_exp_info *info, t_env_list *env, char *str, int key);

#endif
