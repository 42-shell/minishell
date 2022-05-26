/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:18:56 by jkong             #+#    #+#             */
/*   Updated: 2022/05/26 18:34:26 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_flag.h"
#include "string_buffer.h"

char	*parse_matched_pair(char *str, char *open_close, size_t *len_ptr)
{
	size_t			len;
	t_str_buf		*buf;
	int				was_dollar;

	len = 0;
	buf = NULL;
	if (str[len] == open_close[0])
		buf = str_append_raw(buf, &str[len++], 1);
	while (str[len])
	{
		was_dollar = has_flag(get_char_flags(str[len]), CF_EXPANSION);
		buf = str_append_raw(buf, &str[len++], 1);
		if (str[len - 1] == open_close[1])
			break ;
	}
	if (len <= 1 || str[len - 1] != open_close[1])
	{
		//TODO: incompleted pair
	}
	*len_ptr = len;
	return (str_dispose(buf));
}

size_t	parse_quoted_word(t_parse_state *pst, size_t len)
{
	char	open_close[2];
	size_t	nest_len;
	char	*nest_str;

	open_close[0] = pst->str[len];
	open_close[1] = pst->str[len];
	nest_str = parse_matched_pair(&pst->str[len], open_close, &nest_len);
	len += nest_len;
	free(nest_str);
	return (len);
}

t_token_kind	read_token_word(t_parse_state *pst)
{
	size_t		len;
	t_str_buf	*buf;
	t_word		word;

	len = 0;
	buf = NULL;
	while (pst->str[len] && !has_flag(get_char_flags(pst->str[len]), CF_BREAK))
	{
		if (has_flag(get_char_flags(pst->str[len]), CF_QUOTE))
			len = parse_quoted_word(pst, len);
		else
			len++;
	}
	buf = str_append_raw(buf, pst->str, len);
	pst->str += len;
	word.flags = 0;
	word.str = str_dispose(buf);
	free(pst->now_word.str);
	pst->now_word = word;
	return (TK_WORD);
}

t_token_kind	read_token_meta(t_parse_state *pst)
{
	char	tok;

	tok = *pst->str++;
	if (tok == '<' && *pst->str == '<' && pst->str++)
		return (TK_LESS_LESS);
	else if (tok == '>' && *pst->str == '>' && pst->str++)
		return (TK_GREATER_GREATER);
	else if (tok == '&' && *pst->str == '&' && pst->str++)
		return (TK_AND_AND);
	else if (tok == '|' && *pst->str == '|' && pst->str++)
		return (TK_OR_OR);
	if (tok == '&' || tok == ';')
		return (TK_UNDEFINED);
	return (tok);
}

t_token_kind	read_token(t_parse_state *pst)
{
	t_token_kind	result;

	result = TK_UNDEFINED;
	while (has_flag(get_char_flags(*pst->str), CF_BLANK))
		pst->str++;
	if (result == TK_UNDEFINED && !*pst->str)
		result = TK_EOF;
	if (result == TK_UNDEFINED && has_flag(get_char_flags(*pst->str), CF_META))
		result = read_token_meta(pst);
	if (result == TK_UNDEFINED)
		result = read_token_word(pst);
	return (result);
}
