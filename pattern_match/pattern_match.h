/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:14:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/02 01:27:03 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERN_MATCH_H
# define PATTERN_MATCH_H

enum e_file_type
{
	PM_DIRECTORY = 4,
	PM_FILE = 8,
};

enum e_pattern_match_flag
{
	PM_EOF = -1,
	PM_WORD = 0,
	PM_ASTERISK = '*',
	PM_SLASH = '/',
};

typedef struct s_check_done
{
	int		l_name_pos;
	int		r_name_pos;
	int		l_pm_pos;
	int		r_pm_pos;
	int		return_value;
}	t_check_done;

typedef struct s_pattern_flag
{
	int		l_type;
	int		r_type;
}	t_pattern_flag;

typedef struct s_patttern_info
{
	char			*pwd;
	char			**pattern_split;
	int				all;
	int				malloc_size;
	int				split_size;
	int				split_text_cnt;
	int				pm_cnt;
	char			**pm_interleaving;
	t_pattern_flag	pm_flag;
	t_check_done	pm_check;
}	t_pattern_info;

char	**ft_pattern_match(char *pattern);
char	**ft_free_pm(t_pattern_info *info, int key);
void	ft_check_set(t_pattern_info *info, char *name);
void	count_split_size(t_pattern_info *info);
void	pm_strcmp(t_pattern_info *info, int unit, int comp, int type);

#endif
