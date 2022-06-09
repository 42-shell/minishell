/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match_enum.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:22:40 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/09 14:53:53 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERN_MATCH_ENUM_H
# define PATTERN_MATCH_ENUM_H

enum e_free_type
{
	RM_PWD	= 1,
	RM_PM	= 2,
	RM_PI	= 4,
};

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

#endif
