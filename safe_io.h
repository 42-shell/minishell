/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_io.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:55:19 by jkong             #+#    #+#             */
/*   Updated: 2022/06/15 21:24:37 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_IO_H
# define SAFE_IO_H

# include <stdlib.h>
# include <unistd.h>

int		read_safe(int fd, void *buf, size_t len);
void	write_safe(int fd, const void *buf, size_t len);

void	putstr_safe(const char *str);
void	putnbr_safe(int n);
void	puterr_safe(const char *str);

#endif
