/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:36:23 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 20:39:10 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "env_module.h"

static size_t	sort_print_env(t_env_list *head)
{
	t_env_list	**cpy;
	t_env_list	*temp;
	size_t		ret;

	cpy = NULL;
	while (head)
	{
		temp = ft_lstcpy(head, &cpy);
		if (!temp)
		{
			clear_env(cpy);
			return (-1);
		}
		head = head->next;
	}
	ret = print_env(cpy, ON_VISIBLE);
	clear_env(&cpy);
	return (ret);
}

static int	export_syntax_check(char *str)
{
	if (!str || *str == '\0')
		return (-1);
	if ((*str >= 'a' && *str <= 'z') \
		|| (*str >= 'A' && *str <= 'Z') \
		|| (*str == '_'))
		str++;
	else
		return (-1);
	while (*str)
	{
		if ((*str >= 'a' && *str <= 'z') \
			|| (*str >= 'A' && *str <= 'Z') \
			|| (*str == '_') \
			|| (*str >= '0' && *str <= '9'))
			str++;
		else
			return (-1);
	}
	return (0);
}

static size_t	export_strchr(char *str, t_env_list *head)
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

size_t	ft_export(char **argv, t_env_list *head)
{
	size_t		size;

	size = ft_getarr_size(argv);
	if (!size)
		return (sort_print_env(head));
	size = 1;
	while (argv[size])
	{	
		if (export_syntax_check(argv[size]))
		{
			ft_putstr_fd("export: error!", 1);
			ft_putstr_fd(argv[size], 1);
			ft_putstr_fd("\n", 1);
			// error_print(export: not an identifier: str)
		}
		if (export_strchr(argv[size], head))
			return (-1);
		size++;
	}
}
