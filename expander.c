/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:35:56 by jkong             #+#    #+#             */
/*   Updated: 2022/06/19 03:51:08 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*__todo_redirection_expand(t_word *word)
{
	return (word->str);
}

char	*__todo_heredoc_expand(t_word *word, size_t *len_ptr)
{
	size_t	len;
	char	*ptr;

	len = 0;
	while (word->str[len])
		len++;
	*len_ptr = len;
	ptr = malloc(len + 1);
	if (ptr)
	{
		len = 0;
		while (word->str[len])
		{
			ptr[len] = word->str[len];
			len++;
		}
	}
	return (ptr);
}
