/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match_enum.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:22:40 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/14 19:59:02 by jkong            ###   ########.fr       */
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

//TODO: direnv에 있는 매크로로 수정하고 지우기
// #define DT_UNKNOWN       0
// #define DT_FIFO          1
// #define DT_CHR           2
// #define DT_DIR           4
// #define DT_BLK           6
// #define DT_REG           8
// #define DT_LNK          10
// #define DT_SOCK         12
// #define DT_WHT          14
enum e_file_type
{
	PM_DIRECTORY = 4,
	PM_FILE = 8,
};

enum e_pattern_match_value
{
	PM_EOF = -1,
	PM_WORD = 0,
	PM_ASTERISK = '*',
	PM_SLASH = '/',
};

#endif
