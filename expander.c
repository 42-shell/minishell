/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:35:56 by jkong             #+#    #+#             */
/*   Updated: 2022/06/29 21:05:32 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "util_flag.h"
#include "string_buffer.h"
#include "string_vector.h"
#include <unistd.h>

static char	**_expand_general(t_shell *sh, t_word *word)
{
	t_list_word	single;
	t_list_word	*w_list;
	t_list_word	*next_w_list;
	char		**arr;
	char *const	pwd = getcwd(NULL, 0);

	singleton_word_list(&single, word);
	w_list = expand_map(&single, sh->var_list, 1);
	next_w_list = expand_map(w_list, sh->var_list, 2);
	delete_word_list(w_list);
	w_list = next_w_list;
	next_w_list = expand_map(w_list, sh->var_list, 3);
	delete_word_list(w_list);
	w_list = next_w_list;
	arr = expand_collect(w_list, pwd);
	delete_word_list(w_list);
	free(pwd);
	return (arr);
}

char	**word_expand(t_shell *sh, t_list_word *w_list)
{
	t_str_vec	*vec;
	char		**arr;

	vec = NULL;
	while (w_list)
	{
		arr = _expand_general(sh, &w_list->word);
		vec = strv_append_bulk(vec, arr);
		free(arr);
		w_list = w_list->next;
	}
	return (strv_dispose(vec));
}

char	*redir_expand(t_shell *sh, t_word *word)
{
	char		**arr;
	size_t		len;
	char		*str;

	arr = _expand_general(sh, word);
	len = length_strvec(arr);
	if (len != 1)
	{
		free_strvec(arr);
		return (NULL);
	}
	str = arr[0];
	free(arr);
	return (str);
}

void	heredoc_eof_expand(t_word *word)
{
	t_list_word	single;
	t_list_word	*w_list;
	char		*str;

	singleton_word_list(&single, word);
	w_list = expand_map(&single, NULL, 1);
	str = expand_collect_standalone(w_list);
	delete_word_list(w_list);
	if (ft_strcmp(str, word->str) != 0)
	{
		free(word->str);
		word->str = str;
	}
	else
	{
		word->flags = add_flag(word->flags, WF_HAS_DOLLAR);
		free(str);
	}
}

char	*heredoc_expand(t_shell *sh, t_word *word, size_t *len_ptr)
{
	t_list_word	single;
	t_list_word	*w_list;
	t_list_var	*v_list;
	char		*str;

	v_list = sh->var_list;
	singleton_word_list(&single, word);
	w_list = expand_map(&single, v_list, 2);
	str = expand_collect_standalone(w_list);
	delete_word_list(w_list);
	*len_ptr = ft_strlen(str);
	return (str);
}
