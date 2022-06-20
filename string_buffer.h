/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_buffer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:37:17 by jkong             #+#    #+#             */
/*   Updated: 2022/06/20 22:34:08 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_BUFFER_H
# define STRING_BUFFER_H

# include "safe_mem.h"
# include <stdlib.h>

# ifndef INITIAL_CAPACITY
#  define INITIAL_CAPACITY 0x20
# endif

# ifndef GROW_THRESHOLD
#  define GROW_THRESHOLD 0x400
# endif

typedef struct s_str_buf
{
	char	*str;
	size_t	length;
	size_t	capacity;
}	t_str_buf;

t_str_buf	*str_append_raw(t_str_buf *buf, const char *s, size_t n);
t_str_buf	*str_append(t_str_buf *buf, const char *s);
char		*str_dispose(t_str_buf *buf);

#endif
