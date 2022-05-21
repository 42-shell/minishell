/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 20:31:03 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/21 20:31:06 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <stddef.h>

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	char			*type;
}	t_ast;

typedef int	t_gl_func();

/*
** ast_tree_set
*/
void			ast_walk(t_ast *root, t_gl_func *func);
void			ast_set(t_ast *root, t_gl_func *func);
void			ast_attach(t_ast *root, t_ast *left, t_ast *right);
void			ast_delete(t_ast *root);
/*
** ast_tree_info
*/
size_t			ast_size(t_ast *root);
size_t			ast_depth(t_ast *root);

#endif
