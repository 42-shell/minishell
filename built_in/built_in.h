/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:50:31 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/04 18:37:24 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# define PATH_MAX 1024

char		*ft_get_pwd(void);
size_t		ft_pwd(void);
size_t		ft_echo(char **argv);

#endif
