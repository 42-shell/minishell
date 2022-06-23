/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:18:36 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/22 16:26:31 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	set_signal(void)
{
	if (signal(SIGINT, ) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}
