/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:14:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/16 16:21:49 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_H
# define GLOB_H

# include <stddef.h>

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

typedef struct s_check_done
{
	size_t		l_name_pos;
	size_t		l_pt_pos;
	size_t		r_pt_pos;
	int			return_value;
	char		cut_char;
	size_t		cut_pos;
}				t_check_done;

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
	size_t			split_size;
	size_t			split_text_cnt;
	size_t			pattern_pos;
	char			**glob_matched;
	t_pattern_flag	glob_flag;
	t_check_done	pattern_check;
}					t_glob_info;

/*
** Pattern_match function
*/
char	**find_pattern(char *pattern);
int		pm_workhorse(t_glob_info *info);
int		pm_check_string(t_glob_info *info, char *name, int file_type);

/*
** PM_util
*/
char	**ft_free_pm(t_glob_info *info, int key);

#endif
