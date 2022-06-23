/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:16 by jkong             #+#    #+#             */
/*   Updated: 2022/06/23 23:38:34 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef int				t_builtin_res;
typedef char			**t_builtin_argv;
typedef t_list_var		**t_builtin_envp;

typedef t_builtin_res	(*t_builtin_func)(t_builtin_argv, t_builtin_envp);

typedef struct s_builtin_info
{
	const char		*key;
	t_builtin_func	pfn;
}	t_builtin_info;

t_builtin_func	get_builtin(char *name);

t_builtin_res	ft_echo(t_builtin_argv argv, t_builtin_envp envp);
t_builtin_res	ft_cd(t_builtin_argv argv, t_builtin_envp envp);
t_builtin_res	ft_pwd(t_builtin_argv argv, t_builtin_envp envp);
t_builtin_res	ft_export(t_builtin_argv argv, t_builtin_envp envp);
t_builtin_res	ft_unset(t_builtin_argv argv, t_builtin_envp envp);
t_builtin_res	ft_env(t_builtin_argv argv, t_builtin_envp envp);
t_builtin_res	ft_exit(t_builtin_argv argv, t_builtin_envp envp);

#endif
