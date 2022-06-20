/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:45:21 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 16:27:55 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_module.h"
#include "minishell.h"
#include "string_buffer.h"
#include "libft.h" // strcmp
#include "safe_io.h"

void	add_env(t_env_list *env, char *id, char *content, int key)
{
	ft_lstnew(id, content, &env, key);
}

void	del_env(char *id, t_env_list **env)
{
	t_env_list	*lead;
	t_env_list	*follow;

	lead = (*env);
	follow = NULL;
	while (lead)
	{
		if (!ft_strcmp(id, lead->content.id))
		{
			if (follow)
				follow->next = lead->next;
			else
				(*env) = lead->next;
			ft_lstdel(lead);
			break ;
		}
		follow = lead;
		lead = lead->next;
	}
}

void	change_late_cmd(t_env_list *env, char *cmd, int is_built_in)
{
	t_str_buf	*sb;
	char		*temp;

	temp = NULL;
	if (is_built_in == BUILT_IN)
	{
		sb = NULL;
		sb = str_append(sb, get_env(env, "MINISHELL_INIT_PATH"));
		sb = str_append(sb, "/");
		sb = str_append(sb, cmd);
		temp = str_dispose(sb);
	}
	else if (is_built_in == NON_BUILT_IN)
		temp = path_finder(cmd, env);
	del_env("_", &env);
	add_env(env, "_", temp, ON_VISIBLE);
	free(temp);
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
		if ((head->content.visible != HIDE_VISIBLE) \
		&& (key || head->content.visible))
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
