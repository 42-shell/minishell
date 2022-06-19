/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:01:26 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/20 01:44:35 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MODULE_H
# define ENV_MODULE_H

# define NON_VISIBLE 0
# define ON_VISIBLE 1
# define HIDE_VISIBLE -1

# define SKIP_ON 1
# define SKIP_OFF 0

# define BUILT_IN 0
# define NON_BUILT_IN 1

# define EMPTY_CMD 0
# define ERROR_OCCURED 1
# define FAST_DONE 2

# include <stddef.h>

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

void		add_env(t_env_list *env, char *id, char *content, int key);
void		del_env(char *id, t_env_list **env);
char		*get_env(t_env_list *env, char *id);
int			change_env(t_env_list *env, char *id, char *content);

int			env_syntax_check(char *str, int skip_equal);

void		clear_env(t_env_list **env);
void		print_env(t_env_list *env, int key);
char		*path_finder(char *cmd, t_env_list *env);
void		change_late_cmd(t_env_list *env, char *cmd, int is_built_in);

int			dirent_print_error(int key, t_env_list *env);

/*
** list_util
*/
t_env_list	*ft_lstnew(char *id, char *content, t_env_list **head, int key);
t_env_list	*ft_lstcpy(t_env_list *org, t_env_list **cpy);
void		ft_lstclear(t_env_list **lst);
void		ft_lstadd_back(t_env_list **lst, t_env_list *new_lst);
void		ft_lstdel(t_env_list *lst);

#endif
