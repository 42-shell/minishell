/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:46:57 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/17 16:17:11 by yongmkim         ###   ########.fr       */
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

enum e_exp_type
{
	PASS	= 0,
	D_QUOTE = 1,
	S_QUOTE = 2,
	DOLLAR	= 4,
	GLOB	= 8,
};

typedef struct s_exp_info
{
	size_t		cur_pos;
	t_str_buf	*sb;
	t_str_buf	*sb_dollar;
	t_str_vec	*sv;
}				t_exp_info;

/*
** main_function
*/
char	**check_expand(char **argv, t_env_list *head);

#endif
