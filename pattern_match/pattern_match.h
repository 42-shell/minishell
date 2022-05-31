/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:14:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/31 20:33:34 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERN_MATCH_H
# define PATTERN_MATCH_H

typedef enum e_file_type
{
	PM_DIRECTORY = 4,
	PM_FILE = 8,
};

typedef enum e_pattern_match_flag
{
	PM_EOF = -1,
	PM_WORD = 0,
	PM_ASTERISK = '*',
	PM_SLASH = '/',
};

typedef struct s_pattern_flag
{
	int			l_type;
	int			r_type;
}	t_pattern_flag;

typedef struct s_patttern_info
{
	char			*pwd;
	char			**pattern_split;
	int				malloc_size;
	int				pm_cnt;
	char			**pm_interleaving;
	t_pattern_flag	pm_flag;
}	t_pattern_info;

#endif
