/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:36:23 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/16 19:04:03 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h" // getarr_size , strchr
#include "string_buffer.h"
#include "minishell.h"

static size_t	sort_print_env(t_env_list *head)
{
	t_env_list	*cpy;
	t_env_list	*temp;

	cpy = NULL;
	while (head)
	{
		temp = ft_lstcpy(head, &cpy);
		if (!temp)
		{
			clear_env(&cpy);
			return (-1);
		}
		head = head->next;
	}
	print_env(cpy, ON_VISIBLE);
	clear_env(&cpy);
	return (0);
}

static int	export_syntax_check(char *str)
{
	if (!str || *str == '\0')
		return (-1);
	else if (legal_variable_starter(*str))
		str++;
	else
		return (-1);
	while (*str)
	{
		if (legal_variable_char(*str))
			str++;
		else if (*str == '=' || *str == '\0')
			return (0);
		else
			return (-1);
	}
	return (0);
}

static size_t	export_work(char *str, t_env_list *head)
{
	t_env_list	*temp;
	char		*pos;

	pos = ft_strchr(str, '=');
	if (pos)
		str[pos - str] = '\0';
	if (!get_env(head, str))
	{
		if (pos)
			temp = ft_lstnew(str, &str[pos - str + 1], &head, ON_VISIBLE);
		else
			temp = ft_lstnew(str, "", &head, NON_VISIBLE);
		if (!temp)
			return (-1);
	}
	else
	{
		if (pos && change_env(head, str, &str[pos - str + 1]))
			return (-1);
		else if (!pos && change_env(head, str, ""))
			return (-1);
	}
	return (0);
}

// error_print(export: not an identifier: str)
size_t	ft_export(char **argv, t_env_list *head)
{
	size_t		size;

	size = ft_getarr_size(argv);
	if (!size)
		return (-1);
	if (size == 1)
		return (sort_print_env(head));
	size = 1;
	while (argv[size])
	{	
		if (export_syntax_check(argv[size]))
		{
			putstr_safe("export: error:");
			putstr_safe(argv[size]);
			putstr_safe("\n");
		}
		else if (export_work(argv[size], head))
			return (-1);
		size++;
	}
	return (0);
}
