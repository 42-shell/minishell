/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:01:26 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 15:36:34 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MODULE_H
# define ENV_MODULE_H

# define NON_VISIBLE 0
# define ON_VISIBLE 1
# define HIDE_VISIBLE -1

# include <stddef.h>
# include <errno.h>

typedef struct s_env_list
{
	struct s_env_list	*next;
	char				*id;
	char				*content;
	int					visible;
}	t_env_list;

/*
** env
*/
t_env_list	*set_env(char **env);

void		add_env(t_env_list *env, char *id, char *content, int key);
void		del_env(char *id, t_env_list **env);
char		*get_env(t_env_list *env, char *id);
int			change_env(t_env_list *env, char *id, char *content);

int			env_syntax_check(char *str, int skip_equal);

void		clear_env(t_env_list **env);
void		print_env(t_env_list *env, int key);
char		*path_finder(char *cmd, t_env_list *env);

int			dirent_print_error(int key);
char		**env_to_strvec(t_env_list *env);

/*
** list_util
*/
t_env_list	*ft_lstnew(char *id, char *content, t_env_list **head, int key);
t_env_list	*ft_lstcpy(t_env_list *org, t_env_list **cpy);

#endif
