/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:49:02 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 13:03:46 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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

static char	*_subst_ast_to_soh(t_exp_info *info)
{
	char	*temp;
	size_t	idx;

	temp = str_dispose(info->sb);
	idx = 0;
	while (temp[idx])
	{
		if (temp[idx] == '*')
			temp[idx] = SOH;
		idx++;
	}
	return (temp);
}

static void	attach_quote(t_exp_info *info, t_env_list *env, char **str, int key)
{
	if (key == 1)
	{
		info->sb = str_append_raw(info->sb, *str, 1);
		(*str)++;
		(*str) += _d_quote(info, env, *str, EXP_DEQUO);
		if (**str != '\0')
		{
			info->sb = str_append_raw(info->sb, *str, 1);
			(*str)++;
		}
	}
	else
	{
		info->sb = str_append_raw(info->sb, *str, 1);
		(*str)++;
		*str += _s_quote(info, *str);
		if (**str != '\0')
		{
			info->sb = str_append_raw(info->sb, *str, 1);
			(*str)++;
		}
	}
}

static char	*subst_env_and_ast(t_exp_info *info, t_env_list *env, char *str)
{
	while (*str)
	{
		if (*str == '\"')
			attach_quote(info, env, &str, 1);
		else if (*str == '\'')
			attach_quote(info, env, &str, 0);
		else if (has_flag(get_char_flags(*str), CF_EXPANSION))
			str += _dollar(info, env, str);
		else
		{
			info->sb = str_append_raw(info->sb, str, 1);
			str++;
		}
	}
	return (_subst_ast_to_soh(info));
}

static char	*expand_workhorse(t_exp_info *info, t_env_list *env, char *str)
{
	info->sb = str_append(info->sb, "");
	while (*str)
	{
		if (has_flag(get_char_flags(*str), CF_QUOTE))
		{
			if (*str == '\"')
				str += _d_quote(info, env, str, EXP_SUBST);
			else if (*str == '\'' || *str == '`')
				str += _s_quote(info, str);
		}
		else if (has_flag(get_char_flags(*str), CF_EXPANSION))
			str += _dollar(info, env, str);
		else
		{
			info->sb = str_append_raw(info->sb, str, 1);
			str++;
		}
	}
	return (str_dispose(info->sb));
}

char	**check_expand(t_shell *sh, char **argv, t_env_list *env)
{
	t_exp_info	info;
	char		*temp;

	info.sb_dollar = NULL;
	info.sv = NULL;
	info.cur_pos = 0;
	info.last_exit_status = sh->exit_status;
	while (argv && argv[info.cur_pos])
	{
		info.sb = NULL;
		info.sb = str_append(info.sb, "");
		temp = subst_env_and_ast(&info, env, argv[info.cur_pos]);
		temp = expand_workhorse(&info, env, argv[info.cur_pos]);
		if (info.cur_pos && ft_strchr(temp, SOH))
		{
			info.sv = expand_glob(temp, info.sv, env);
			free(temp);
		}
		else
			info.sv = strv_append(info.sv, temp);
		info.cur_pos++;
	}
	return (strv_dispose(info.sv));
}
