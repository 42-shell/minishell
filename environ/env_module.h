/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:01:26 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 15:55:28 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_SET_H
# define ENV_SET_H

# include <stddef.h>

enum e_env_type
{
	other = 0,
	path,
	old_pwd,
	home,
};

typedef struct s_content
{
	char	*id;
	char	*content;
}			t_content;

typedef struct s_env_list
{
	struct s_env_list	*next;
	struct s_content	content;
}						t_env_list;

/*
** env
*/
t_env_list	*set_env(char **env);
char		*get_env(t_env_list *head, char *id);
size_t		print_env(t_env_list *head);
void		clear_env(t_env_list **head);

/*
** string_util
*/
char		*ft_strchr(char *s, int c);
char		*ft_strdup(const char *s1);
size_t		ft_strcmp(char *s1, char *s2);

/*
** list_util
*/
t_env_list	*ft_lstnew(char *id, char *content, t_env_list **head);
void		ft_lstclear(t_env_list **lst);
void		ft_lstdel(t_env_list *lst);

#endif
