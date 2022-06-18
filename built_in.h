/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:50:31 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/19 02:32:45 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include <stddef.h>
# include "env_module.h"
# include "minishell.h"

# define EMPTY_CMD 0
# define ERROR_OCCURED 1
# define FAST_DONE 2

char		*ft_get_pwd(void);
size_t		ft_pwd(char **argv, t_env_list *env);
size_t		ft_echo(char **argv, t_env_list *env);
size_t		ft_cd(char **argv, t_env_list *env);
size_t		ft_env(char **argv, t_env_list *env);
size_t		ft_export(char **argv, t_env_list *env);
size_t		ft_unset(char **argv, t_env_list **env);
int			ft_exit(char **argv, t_env_list *env);

#endif
