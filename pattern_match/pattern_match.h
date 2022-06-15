/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:14:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/15 19:30:33 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERN_MATCH_H
# define PATTERN_MATCH_H

# include <stddef.h>

typedef struct s_check_done
{
	size_t		l_name_pos;
	size_t		l_pm_pos;
	size_t		r_pm_pos;
	int			return_value;
	char		cut_char;
	size_t		cut_pos;
}				t_check_done;

typedef struct s_pattern_flag
{
	int		l_type;
	int		r_type;
}			t_pattern_flag;

typedef struct s_patttern_info
{
	char			*pwd;
	char			**pattern_split;
	size_t			malloc_size;
	size_t			split_size;
	size_t			split_text_cnt;
	size_t			pm_pos;
	char			**pm_interleaving;
	t_pattern_flag	pm_flag;
	t_check_done	pm_check;
}					t_pattern_info;

/*
** Pattern_match function
*/
char	**ft_pattern_match(char *pattern);
int		pm_workhorse(t_pattern_info *info);
int		pm_check_string(t_pattern_info *info, char *name, int file_type);

/*
** PM_util
*/
char	**ft_free_pm(t_pattern_info *info, int key);

#endif
