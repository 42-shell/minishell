/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:35:56 by jkong             #+#    #+#             */
/*   Updated: 2022/06/23 20:31:29 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "safe_mem.h"
#include "util_flag.h"
#include "string_buffer.h"
#include "string_vector.h"
#include "generic_list.h"
#include <unistd.h>

t_str_vec	*expand(t_str_vec *vec, t_shell *sh, t_word *word, int glob)
{
	t_list_word	*ew_list;
	char		*str;
	char		*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		exit(EXIT_FAILURE);
	ew_list = new_expand_word_list(word);
	str = join_expand_word_list(ew_list, sh->var_list, glob);
	vec = file_expand(vec, pwd, str);
	free(str);
	delete_expand_word_list(ew_list);
	free(pwd);
	return (vec);
}

t_str_vec	*expand_list(t_str_vec *vec, t_shell *sh, t_list_word *w_list,
	int glob)
{
	while (w_list)
	{
		vec = expand(vec, sh, &w_list->word, glob);
		w_list = w_list->next;
	}
	return (vec);
}

char	*expand_redir(t_shell *sh, t_word *word, int glob)
{
	t_str_vec	*vec;
	char		**arr;
	size_t		len;
	char		*str;

	vec = expand(NULL, sh, word, glob);
	len = vec->length;
	arr = strv_dispose(vec);
	if (len != 1)
	{
		free_strvec(arr);
		return (NULL);
	}
	str = arr[0];
	free(arr);
	return (str);
}

void	expand_heredoc_eof(t_word *word)
{
	t_list_word	*ew_list;
	char		*str;

	ew_list = new_expand_word_list(word);
	str = join_expand_word_list(ew_list, NULL, 0);
	delete_expand_word_list(ew_list);
	if (ft_strcmp(str, word->str) != 0)
	{
		free(word->str);
		word->str = str;
		set_flag(&word->flags, WF_UNQUOTED);
	}
	else
		free(str);
}

char	*expand_heredoc(t_shell *sh, t_word *word, size_t *len_ptr)
{
	t_list_word	*ew_list;
	t_list_var	*ev_list;
	char		*str;

	ew_list = new_expand_word_list(word);
	ev_list = sh->var_list;
	if (has_flag(word->flags, WF_UNQUOTED))
		ev_list = NULL;
	str = join_expand_word_list(ew_list, ev_list, 0);
	delete_expand_word_list(ew_list);
	*len_ptr = ft_strlen(str);
	return (str);
}
