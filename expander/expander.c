/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:49:02 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/16 18:59:17 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"

// A = ''
//echo	A	'A$A'	"A$A"	l $'AB$A'	$"AC$A" l	'$AB'	"$A$A"
//res	A	A$A		A 		l AB 		$AC 	l	$A
//
//echo	"b'$A'b"	'b"$A"b'
//res	b'BBB'b		b"$A"b
//
//export 'B''A''B'=BBBB
//BAB=BBBB
//-> quote remove (first quote match)
//-> if remain other type quote -> error

//$? -> exit status
//$*, $@ -> non systax[letter | _ ][letter | digit | _ ]^*-> error
//
//
//$ -> SQ -> not interpret
//-> DQ or Out -> interpret
//
//$VALUE -> 없으면 문자열 이어 붙이기 : stitch A-B
//

// DQ, SQ : match -> if null_terminate -> error
static void	init_expand_info(t_exp_info *info)
{
	info->cur_pos = 0;
	info->exp_output = NULL;
	info->str_buf = NULL;
	info->str_vec = NULL;
}

static 

char	**check_expand(char **argv, t_env_list *head)
{
	t_exp_info	info;

	if (!argv || !(*argv) || !head)
		return (NULL);
	init_expand_info(&info);
	while (argv[info.cur_pos])
	{
		// 1. check env, del_quote -> str_append(str_buf, str);
		// 2. stitch 'null'-case -> str_append(str_buf, str);
		expand_env(info, argv[info.cur_pos]);
		if (info.cur_pos && ft_strchr(info.str_buf->str, "*"))
			info-.str_vec \
				= strv_append(info->str_vec, expand_glob(info.str_buf->str));
		else
			info->str_vec \
				= strv_append(info->str_vec, str_dispose(info.str_buf));
		info->str_buf = NULL;
		info.cur_pos++;
	}
	return (strv_dispose(info->str_vec));
}
