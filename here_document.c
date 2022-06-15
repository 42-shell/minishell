/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 19:01:17 by jkong             #+#    #+#             */
/*   Updated: 2022/06/15 21:28:09 by jkong            ###   ########.fr       */
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
		puterr_safe("maximum here-document count exceeded");
		exit(EXIT_FAILURE);
	}
	pst->here_document[pst->here_document_index++] = r;
}

static char	*_read_document(char *eof)
{
	t_str_buf	*sb;
	char		*str;

	sb = NULL;
	while (1)
	{
		str = readline("> ");
		if (!str || ft_strcmp(str, eof) == 0)
			break ;
		sb = str_append(sb, str);
		sb = str_append(sb, "\n");
		free(str);
	}
	return (str_dispose(sb));
}

static void	_make_here_document(t_list_redirect *r)
{
	t_word		word;
	t_word		document;

	ft_memset(&word, 0, sizeof(word));
	ft_memset(&document, 0, sizeof(document));
	swap_word(&word, &r->redirect.word);
	document.str = _read_document(word.str);
	swap_word(&r->redirect.word, &document);
	dispose_word(&word);
	dispose_word(&document);
}

void	gather_here_document(t_parser *pst)
{
	size_t	i;
	size_t	n;

	n = pst->here_document_index;
	i = 0;
	while (i < n)
	{
		_make_here_document(pst->here_document[i]);
		pst->here_document[i] = NULL;
		i++;
	}
	pst->here_document_index = 0;
}
