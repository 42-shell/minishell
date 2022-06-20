/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:50:31 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/21 08:11:31 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include <stddef.h>
# include "env_module.h"
# include "minishell.h"

# define HOME 0
# define OUTSIDE 1

typedef int	(*t_built_in_func)(char **, t_env_list **);

typedef struct s_built_in_info
{
	const char		*key;
	t_built_in_func	pfn;
}	t_built_in_info;

t_built_in_func	get_built_in(char *name);
char			*ft_get_pwd(void);

int				ft_pwd(char **argv, t_env_list **env);
int				ft_echo(char **argv, t_env_list **env);
int				ft_cd(char **argv, t_env_list **env);
int				ft_env(char **argv, t_env_list **env);
int				ft_export(char **argv, t_env_list **env);
int				ft_unset(char **argv, t_env_list **env);
int				ft_exit(char **argv, t_env_list **env);

#endif
