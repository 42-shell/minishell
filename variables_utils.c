/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:32:39 by jkong             #+#    #+#             */
/*   Updated: 2022/06/28 02:58:34 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_flag.h"
#include "safe_mem.h"
#include "libft.h"
#include "string_buffer.h"
#include "string_vector.h"
#include "generic_list.h"
#include <stdint.h>

static const uint32_t		g_legal_variable_starter[] = {
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	/*														*/
	/*			** ?>=< ;:98 7654 3210  /.-, +*)( '&%$ #"!  */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	/*														*/
	/*			** _^]\ [ZYX WVUT SRQP  ONML KJIH GFED CBA@ */
	0x87fffffe, /* 1000 0111 1111 1111  1111 1111 1111 1110 */
	/*														*/
	/*			**  ~}| {zyx wvut srqp  onml kjih gfed cba` */
	0x07fffffe, /* 0000 0111 1111 1111  1111 1111 1111 1110 */
	/*														*/
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
};

static const uint32_t		g_legal_variable_char[] = {
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	/*														*/
	/*			** ?>=< ;:98 7654 3210  /.-, +*)( '&%$ #"!  */
	0x03ff0000, /* 0000 0011 1111 1111  0000 0000 0000 0000 */
	/*														*/
	/*			** _^]\ [ZYX WVUT SRQP  ONML KJIH GFED CBA@ */
	0x87fffffe, /* 1000 0111 1111 1111  1111 1111 1111 1110 */
	/*														*/
	/*			**  ~}| {zyx wvut srqp  onml kjih gfed cba` */
	0x07fffffe, /* 0000 0111 1111 1111  1111 1111 1111 1110 */
	/*														*/
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
};

int	is_legal_variable(const char *s, size_t *index_ptr)
{
	if (legal_condition(g_legal_variable_starter, s[*index_ptr]))
	{
		(*index_ptr)++;
		while (legal_condition(g_legal_variable_char, s[*index_ptr]))
			(*index_ptr)++;
		return (1);
	}
	return (0);
}

char	*alloc_str_pair(const char *s, char **val_ptr, char delim)
{
	const size_t	len = ft_strlen(s) + 1;
	char *const		dup = ft_memcpy(calloc_safe(len, sizeof(char)), s, len);
	char *const		val = ft_strchr(dup, delim);

	if (val)
	{
		*val = '\0';
		*val_ptr = val + 1;
	}
	else
		*val_ptr = NULL;
	return (dup);
}

void	strvec_to_var_list(t_list_var **list_ptr, char **arr, t_var_flags attr)
{
	char		**vec;
	char		*temp;
	char		*value;

	vec = arr;
	while (*vec)
	{
		temp = alloc_str_pair(*vec, &value, '=');
		put_var(list_ptr, temp, value, attr);
		free(temp);
		vec++;
	}
}

char	**var_list_to_strvec(t_list_var *list, t_var_flags attr)
{
	t_str_vec	*vec;
	t_str_buf	*buf;

	vec = NULL;
	while (list)
	{
		if ((list->attr & attr) == attr && list->value)
		{
			buf = str_append_format(NULL, "%s=%s", list->name, list->value);
			vec = strv_append(vec, str_dispose(buf));
		}
		list = list->next;
	}
	return (strv_dispose(vec));
}

void	dispose_var_list(t_list_var *list)
{
	t_list_var	*next;

	while (list)
	{
		next = list->next;
		free(list->name);
		free(list->value);
		free(list);
		list = next;
	}
}
