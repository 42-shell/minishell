/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:05:35 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/25 17:23:54 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_sig.h"

int	ft_signal(void)
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
}
