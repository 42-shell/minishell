/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_flag.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:51:56 by jkong             #+#    #+#             */
/*   Updated: 2022/05/22 02:42:12 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_FLAG_H
# define UTIL_FLAG_H

void	set_flag(int *ptr, int index);
void	reset_flag(int *ptr, int index);
int		has_flag(int flags, int index);

#endif
