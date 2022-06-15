/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <yongmkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:41:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/15 21:11:02 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h" // getarr_size
#include <unistd.h> // chdir

//old_pwd ??? ~, - 
size_t	ft_cd(char **argv, t_env_list *head)
{
	int		size;
	char	*id;

	size = ft_getarr_size(argv);
	if (!size || size > 2)
		return (-1);
	if (size == 1)
	{
		id = get_env(head, "HOME");
		if (!id)
			return (0);
		else if (chdir(id))
			return (-1);
	}
	else if (size == 2)
	{
		if (chdir(argv[1]))
			return (-1);
	}
	return (0);
}
