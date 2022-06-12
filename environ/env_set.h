/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:01:26 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/13 00:17:48 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_SET_H
# define ENV_SET_H

enum e_env_type
{
	other = 0,
	path,
	old_pwd,
	home,
};

typedef struct s_content
{
	char	*name;
	int		type;
	char	**value;
}			t_content;

typedef struct s_env_list
{
	struct s_envlist	*next;
	struct s_content	content;
}						t_env_list;

#endif
