/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:46:57 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 06:41:27 by jkong            ###   ########.fr       */
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
void	expand_other_case(t_exp_info *info, char *str, size_t *ret);

#endif
