/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:18:34 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/16 11:27:18 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "string_buffer.h"
#include "safe_io.h"

//quote = key && (!head->content.visible || !head->content.content);
//
static void	str_manage(t_str_buf *sb)
{
	char	*str;

	str = str_dispose(sb);
	putstr_safe(str);
	free(str);
}

void	print_env(t_env_list *head, int key)
{
	t_str_buf	*sb;

	sb = NULL;
	while (head)
	{
		if (key || head->content.visible)
		{
			if (key)
				sb = str_append(sb, "declare -x ");
			sb = str_append(sb, head->content.id);
			if (head->content.visible)
			{
				sb = str_append(sb, "=");
				if (key)
					sb = str_append(sb, "\"");
				sb = str_append(sb, head->content.content);
				if (key)
					sb = str_append(sb, "\"");
			}
			sb = str_append(sb, "\n");
		}
		head = head->next;
	}
	str_manage(sb);
}
