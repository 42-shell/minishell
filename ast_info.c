/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 21:16:58 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/21 21:17:01 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

size_t	ast_size(t_ast *root)
{
	if (root)
		return (0);
	else
		return (1 + ast_size(root->left) + ast_size(root->right));
}

size_t	ast_depth(t_ast *root)
{
	size_t	left_depth;
	size_t	right_depth;

	if (root == NULL)
		return (-1);
	else
	{
		left_depth = ast_depth(root->left);
		right_depth = ast_depth(root->right);
		if (right_depth > left_depth)
			return (1 + right_depth);
		else
			return (1 + left_depth);
	}
}
