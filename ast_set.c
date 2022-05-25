/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 20:26:02 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/25 17:02:48 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ast_set(t_ast *root, t_gl_func *func)
{
	if (root)
	{
		(*func)(root);
	}
}

void	ast_walk(t_ast *root, t_gl_func *func)
{
	if (root)
	{
		if ((*func)(root) < 0)
			return ;
		if (root->left)
			ast_walk(root->left, func);
		if (root->right)
			ast_walk(root->right, func);
	}
}

void	ast_attach(t_ast *root, t_ast *left, t_ast *right)
{
	if (root)
	{
		root->left = left;
		root->right = right;
	}
}

static void	ast_free(t_ast *node)
{
	free(node->type);
	free(node);
}

void	ast_delete(t_ast *root)
{
	if (root == NULL)
		return ;
	if (root->left)
		ast_delete(root->left);
	if (root->right)
		ast_delete(root->right);
	ast_free(root);
}
