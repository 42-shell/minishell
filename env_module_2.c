/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:45:21 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 07:31:59 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "minishell.h"
#include "string_buffer.h"
#include "libft.h" // strcmp
#include "safe_io.h"
#include "generic_list.h"

void	add_env(t_env_list *env, char *id, char *content, int key)
{
	ft_lstnew(id, content, &env, key);
}

static int	_env_cmp(t_env_list *t, void *arg)
{
	return (ft_strcmp(t->id, arg) == 0);
}

void	del_env(char *id, t_env_list **env)
{
	t_env_list	*del;

	del = (void *)list_remove((void *)env, _env_cmp, id);
	free(del->id);
	free(del->content);
	free(del);
}

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
		if ((head->visible != HIDE_VISIBLE) \
		&& (key || head->visible))
		{
			if (key)
				sb = str_append(sb, "declare -x ");
			sb = str_append(sb, head->id);
			if (head->visible)
			{
				sb = str_append(sb, "=");
				if (key)
					sb = str_append(sb, "\"");
				sb = str_append(sb, head->content);
				if (key)
					sb = str_append(sb, "\"");
			}
			sb = str_append(sb, "\n");
		}
		head = head->next;
	}
	str_manage(sb);
}
