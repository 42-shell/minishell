/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:14:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/17 19:25:31 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_H
# define GLOB_H

# include <stddef.h>
# include "string_vector.h"

# include <stdio.h> // need to del

# define LHS 1
# define RHS -1

enum e_free_type
{
	RM_PWD	= 1,
	RM_PM	= 2,
	RM_PI	= 4,
};

enum e_pattern_match_value
{
	PM_EOF = -1,
	PM_WORD = 0,
	PM_ASTERISK = '*',
	PM_SLASH = '/',
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
t_str_vec	*expand_glob(char *pattern, t_str_vec *str_vec);
int			glob_workhorse(t_glob_info *info);
int			check_string(t_glob_info *info, char *name, int file_type);

/*
** PM_util
*/
t_str_vec	*ft_free_pm(t_glob_info *info, int key);

#endif
