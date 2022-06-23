/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mem.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:55:19 by jkong             #+#    #+#             */
/*   Updated: 2022/06/23 22:48:56 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_MEM_H
# define SAFE_MEM_H

# include <stdlib.h>

void	*malloc_safe(size_t size);
void	*calloc_safe(size_t count, size_t size);
int		free_safe(void *ptr);

#endif
