/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:14:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 14:23:25 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_H
# define GLOB_H

# include <stddef.h>
# include "string_vector.h"
# include "env_module.h"

enum e_glob_hand_side
{
	GLOB_LHS	= 1,
	GLOB_RHS	= -1,
};

enum e_free_type
{
	RM_PATTERN_SPLIT	= 1,
	RM_STR_VEC			= 2,
};

enum e_pattern_match_value
{
	GLOB_EOF		= -1,
	GLOB_WORD		= 0,
	GLOB_ASTERISK	= 1,
	GLOB_SLASH		= '/',
	GLOB_DOT		= '.',
};

typedef struct s_check_info
{
	size_t		name_pos;
	size_t		l_pt_pos;
	size_t		r_pt_pos;
	int			return_value;
	char		cut_char;
	size_t		cut_pos;
}				t_check_info;

typedef struct s_glob_flag
{
	int		l_type;
	int		r_type;
}			t_glob_flag;

typedef struct s_glob_info
{
	char			*pwd;
	char			**pattern_split;
	size_t			malloc_size;
	size_t			split_text_cnt;
	size_t			split_size;
	t_str_vec		*glob_matched;
	t_glob_flag		glob_flag;
	t_check_info	check_info;
}					t_glob_info;

/*
** Pattern_match function
*/
t_str_vec	*expand_glob(char *pattern, t_str_vec *str_vec, t_env_list *env);
int			glob_workhorse(t_glob_info *info);
int			check_string(t_glob_info *info, char *name, int file_type);

/*
** PM_util
*/
t_str_vec	*ft_free_pm(t_glob_info *info, int key);

#endif
