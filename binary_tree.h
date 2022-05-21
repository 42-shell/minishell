/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 20:31:03 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/21 20:31:06 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
# define BINARY_TREE_H

# include <stddef.h>

typedef struct s_binary_tree
{
	struct s_binary_tree	*left;
	struct s_binary_tree	*right;
}	t_binary_tree;



#endif
