/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:18:34 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/15 19:18:59 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "string_buffer.h"

size_t	print_env(t_env_list *head, int key)
{
	t_str_buf	*sb;
	char		*str;
	int			quote;

	sb = NULL;
	while (head)
	{
		if (key || head->content.visible)
		{
			quote = key && (!head->content.visible || !head->content.content);
			sb = str_append(sb, head->content.id);
			sb = str_append(sb, "=");
			if (quote)
				sb = str_append(sb, "\'");
			sb = str_append(sb, head->content.content);
			if (quote)
				sb = str_append(sb, "\'");
			sb = str_append(sb, "\n");
		}
		head = head->next;
	}
	str = str_dispose(sb);
	putstr_safe(str);
	free(str);
	return (0);
}
