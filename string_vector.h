/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_vector.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:37:17 by jkong             #+#    #+#             */
/*   Updated: 2022/06/19 14:52:40 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_VECTOR_H
# define STRING_VECTOR_H

# include "safe_mem.h"
# include <stdlib.h>

# ifndef INITIAL_CAPACITY_V
#  define INITIAL_CAPACITY_V 0x4
# endif

# ifndef GROW_THRESHOLD_V
#  define GROW_THRESHOLD_V 0x20
# endif

typedef struct s_str_vec
{
	char	**arr;
	size_t	length;
	size_t	capacity;
}	t_str_vec;

t_str_vec	*strv_append(t_str_vec *vec, char *s);
t_str_vec	*strv_append_bulk(t_str_vec *vec, char **arr);
char		**strv_dispose(t_str_vec *vec);
void		free_strvec(char **arr);

#endif
