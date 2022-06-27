/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 19:01:17 by jkong             #+#    #+#             */
/*   Updated: 2022/06/28 02:39:52 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_buffer.h"
#include "safe_io.h"
#include "libft.h"
#include <unistd.h>

void	push_here_document(t_parser *pst, t_list_redirect *r)
{
	if (pst->here_document_index >= HERE_DOCUMENT_MAX)
	{
		print_err("maximum here-document count exceeded\n");
		exit(EXIT_FAILURE);
	}
	pst->here_document[pst->here_document_index++] = r;
}

char	*read_document(char *eof, t_shell *sh)
{
	t_str_buf	*buf;
	char		*str;
	int			line;

	buf = NULL;
	line = 0;
	while (1)
	{
		str = readline(get_var(sh->var_list, "PS2"));
		line++;
		if (!str)
		{
			print_err("here-document at line %d "
				"delimited by end-of-file (wanted `%s')\n", line, eof);
			break ;
		}
		if (ft_strcmp(str, eof) == 0)
		{
			free(str);
			break ;
		}
		buf = str_append_format(buf, "%s\n", str);
		free(str);
	}
	return (str_dispose(buf));
}

static int	_make_here_document(t_list_redirect *r, t_shell *sh)
{
	t_word		word;
	t_word		document;

	ft_memset(&word, 0, sizeof(word));
	ft_memset(&document, 0, sizeof(document));
	swap_word(&word, &r->redirect.word);
	heredoc_eof_expand(&word);
	document.str = read_document_pipe(word.str, sh);
	document.flags = word.flags;
	swap_word(&r->redirect.word, &document);
	dispose_word(&word);
	dispose_word(&document);
	if (g_exit_status != EXIT_SUCCESS)
	{
		free(r->redirect.word.str);
		r->redirect.word.str = NULL;
	}
	return (!r->redirect.word.str);
}

int	gather_here_document(t_parser *pst, t_shell *sh)
{
	size_t	i;
	size_t	n;
	int		result;

	n = pst->here_document_index;
	i = 0;
	result = 0;
	while (i < n)
	{
		if (result == 0)
			result |= _make_here_document(pst->here_document[i], sh);
		else
			dispose_word(&pst->here_document[i]->redirect.word);
		pst->here_document[i] = NULL;
		i++;
	}
	pst->here_document_index = 0;
	return (result);
}
