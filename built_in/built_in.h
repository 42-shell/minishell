/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:50:31 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/14 22:04:08 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

//TODO: #include <limits.h>로 대체
# define PATH_MAX 1024
# include <stddef.h>
# include "env_module.h"
# include <stdio.h> /// need to delete

char		*ft_get_pwd(void);
size_t		ft_pwd(char **argv);
size_t		ft_echo(char **argv);
size_t		ft_cd(char **argv);
size_t		ft_env(char **argv, t_env_list *head);
size_t		ft_export(char **argv, t_env_list *head);
size_t		ft_unset(char **argv, t_env_list **head);

/*
** util
*/
size_t		ft_getarr_size(char **argv);
size_t		ft_putchar_fd(char c, int fd);
size_t		ft_putstr_fd(char *str, int fd);

#endif
