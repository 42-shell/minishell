/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:01:26 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/16 11:26:29 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MODULE_H
# define ENV_MODULE_H

# define NON_VISIBLE 0
# define ON_VISIBLE 1

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
	int		visible;
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
void		print_env(t_env_list *head, int key);
void		clear_env(t_env_list **head);
size_t		change_env(t_env_list *head, char *id, char *content);

/*
** list_util
*/
t_env_list	*ft_lstnew(char *id, char *content, t_env_list **head, int key);
void		ft_lstclear(t_env_list **lst);
void		ft_lstadd_back(t_env_list **lst, t_env_list *new);
void		ft_lstdel(t_env_list *lst);
t_env_list	*ft_lstcpy(t_env_list *org, t_env_list **cpy);

#endif
