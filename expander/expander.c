/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:49:02 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/16 15:58:08 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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
static void	ft_init_expand_info(t_exp_info *info)
{
	info->malloc_size = 1;
	info->cur_src_pos = 0;
	info->cur_pos = 0;
	info->exp_output = NULL;
}

char	**check_expand(char **argv, t_env_list *head)
{
	t_exp_info	info;

	if (!argv || !(*argv) || !head)
		return (NULL);
	ft_init_expand_info(&info);
	while (argv[info.cur_src_pos])
	{
		// check expand, syntax
		// -> expand
		// -> add to exp_output;
		info.cur_src_pos++;
	}
	return (info.exp_output);
}
