/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:49:02 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/16 22:25:31 by yongmkim         ###   ########.fr       */
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

//$*, $@ -> non systax[letter | _ ][letter | digit | _ ]^*-> error
//
//
//$ -> SQ -> not interpret
//-> DQ or Out -> interpret
//
// DQ, SQ : match -> if null_terminate -> error




// 1. check env, del_quote -> str_append(str_buf, str);
// 2. stitch 'null'-case -> str_append(str_buf, str);
//

// $ case
// -> $? -> exit_status

// DQ_case

// SQ_ CASE
	
static void	

static void	expand_workhorse(t_exp_info *info, t_env_list *head, char *str)
{
	char	*temp;

	while (*str)
	{
		if (has_flag(get_char_flags(*str), CF_QUOTE))
		{
			if (*str == "\"")
				expand_double_quote();
			else if (*str == "\'")
				expand_single_quote();
		}
		else if (has_flag(get_char_flags(*str), CF_EXPANSION))
		{
			expand_dollar();
		}
		else 
		{
			info->s_b = str_append_raw(info->s_b, str, 1);
			str++;
		}
	}
	return (str_dispose(info->s_b));
}

char	**check_expand(char **argv, t_env_list *head)
{
	t_exp_info	info;
	char		*temp;

	if (!argv || !(*argv) || !head)
		return (NULL);
	info->s_b = NULL;
	info->s_v = NULL;
	info->cur_pos = 0;
	while (argv[info.cur_pos])
	{
		temp = expand_workhorse(info, head, argv[info.cur_pos]);
		if (info.cur_pos && ft_strchr(info.s_b->str, "*"))
			info-.s_v = strv_append_bulk(info->s_v, expand_glob(info.s_b->str));
		else
			info->s_v = strv_append(info->s_v, temp);
		info->s_b = NULL;
		info.cur_pos++;
	}
	return (strv_dispose(info->s_v));
}
