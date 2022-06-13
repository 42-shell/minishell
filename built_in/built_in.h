/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:50:31 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 21:39:49 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

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
