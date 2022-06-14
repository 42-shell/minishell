/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:49:02 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/14 11:28:23 by yongmkim         ###   ########.fr       */
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

char **check_expand(char **argv, t_env_list *head)
{
	if (!argv || !(*argv) || !head)
		return (NULL);
}
