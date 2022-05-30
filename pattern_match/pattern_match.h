/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:14:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/30 20:25:16 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERN_MATCH_H
# define PATTERN_MATCH_H
# include <dirent.h>

typedef enum e_pattern_match
{
	PM_EOF = 0,
	PM_ASTERISK = '*',
	PM_SLASH = '/',
	PM_WORD,
}	t_pattern_match;

typedef struct s_patttern_match
{
	int			l_type;
	int			r_type;
	int			pm_idx;
	char		*pwd;
	char		**interleaving;
}	t_pattern_match;

#endif
