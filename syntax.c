/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:18:56 by jkong             #+#    #+#             */
/*   Updated: 2022/06/17 01:18:00 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdint.h>

static const uint32_t		g_legal_variable_starter[] = {
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	/*														*/
	/*			** ?>=< ;:98 7654 3210  /.-, +*)( '&%$ #"!  */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	/*														*/
	/*			** _^]\ [ZYX WVUT SRQP  ONML KJIH GFED CBA@ */
	0x87fffffe, /* 1000 0111 1111 1111  1111 1111 1111 1110 */
	/*														*/
	/*			**  ~}| {zyx wvut srqp  onml kjih gfed cba` */
	0x07fffffe, /* 0000 0111 1111 1111  1111 1111 1111 1110 */
	/*														*/
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
};

static const uint32_t		g_legal_variable_char[] = {
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	/*														*/
	/*			** ?>=< ;:98 7654 3210  /.-, +*)( '&%$ #"!  */
	0x03ff0000, /* 0000 0011 1111 1111  0000 0000 0000 0000 */
	/*														*/
	/*			** _^]\ [ZYX WVUT SRQP  ONML KJIH GFED CBA@ */
	0x87fffffe, /* 1000 0111 1111 1111  1111 1111 1111 1110 */
	/*														*/
	/*			**  ~}| {zyx wvut srqp  onml kjih gfed cba` */
	0x07fffffe, /* 0000 0111 1111 1111  1111 1111 1111 1110 */
	/*														*/
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
	0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
};

static const t_char_flags	g_syn_table[256] = {
	CFV_WORD,				/* 0 */
	CFV_SPECIAL,			/* CTLESC */
	CFV_WORD,				/* 2 */
	CFV_WORD,				/* 3 */
	CFV_WORD,				/* 4 */
	CFV_WORD,				/* 5 */
	CFV_WORD,				/* 6 */
	CFV_WORD,				/* \a */
	CFV_WORD,				/* \b */
	CFV_BREAK | CFV_BLANK,	/* \t */
	CFV_BREAK,				/* \n */
	CFV_WORD,				/* \v */
	CFV_WORD,				/* \f */
	CFV_WORD,				/* \r */
	CFV_WORD,				/* 14 */
	CFV_WORD,				/* 15 */
	CFV_WORD,				/* 16 */
	CFV_WORD,				/* 17 */
	CFV_WORD,				/* 18 */
	CFV_WORD,				/* 19 */
	CFV_WORD,				/* 20 */
	CFV_WORD,				/* 21 */
	CFV_WORD,				/* 22 */
	CFV_WORD,				/* 23 */
	CFV_WORD,				/* 24 */
	CFV_WORD,				/* 25 */
	CFV_WORD,				/* 26 */
	CFV_WORD,				/* ESC */
	CFV_WORD,				/* 28 */
	CFV_WORD,				/* 29 */
	CFV_WORD,				/* 30 */
	CFV_WORD,				/* 31 */
	CFV_BREAK | CFV_BLANK,	/* SPC */
	CFV_WORD,				/* ! */
	CFV_QUOTE,				/* " */
	CFV_WORD,				/* # */
	CFV_EXPANSION,			/* $ */
	CFV_WORD,				/* % */
	CFV_META | CFV_BREAK,	/* & */
	CFV_QUOTE,				/* ' */
	CFV_META | CFV_BREAK,	/* ( */
	CFV_META | CFV_BREAK,	/* ) */
	CFV_GLOB,				/* * */
	CFV_WORD,				/* + */
	CFV_WORD,				/* , */
	CFV_WORD,				/* - */
	CFV_WORD,				/* . */
	CFV_WORD,				/* / */
	CFV_WORD,				/* 0 */
	CFV_WORD,				/* 1 */
	CFV_WORD,				/* 2 */
	CFV_WORD,				/* 3 */
	CFV_WORD,				/* 4 */
	CFV_WORD,				/* 5 */
	CFV_WORD,				/* 6 */
	CFV_WORD,				/* 7 */
	CFV_WORD,				/* 8 */
	CFV_WORD,				/* 9 */
	CFV_WORD,				/* : */
	CFV_WORD,				/* ; */
	CFV_META | CFV_BREAK,	/* < */
	CFV_WORD,				/* = */
	CFV_META | CFV_BREAK,	/* > */
	CFV_GLOB,				/* ? */
	CFV_WORD,				/* @ */
	CFV_WORD,				/* A */
	CFV_WORD,				/* B */
	CFV_WORD,				/* C */
	CFV_WORD,				/* D */
	CFV_WORD,				/* E */
	CFV_WORD,				/* F */
	CFV_WORD,				/* G */
	CFV_WORD,				/* H */
	CFV_WORD,				/* I */
	CFV_WORD,				/* J */
	CFV_WORD,				/* K */
	CFV_WORD,				/* L */
	CFV_WORD,				/* M */
	CFV_WORD,				/* N */
	CFV_WORD,				/* O */
	CFV_WORD,				/* P */
	CFV_WORD,				/* Q */
	CFV_WORD,				/* R */
	CFV_WORD,				/* S */
	CFV_WORD,				/* T */
	CFV_WORD,				/* U */
	CFV_WORD,				/* V */
	CFV_WORD,				/* W */
	CFV_WORD,				/* X */
	CFV_WORD,				/* Y */
	CFV_WORD,				/* Z */
	CFV_GLOB,				/* [ */
	CFV_WORD,				/* \ */
	CFV_GLOB,				/* ] */
	CFV_GLOB,				/* ^ */
	CFV_WORD,				/* _ */
	CFV_QUOTE,				/* ` */
	CFV_WORD,				/* a */
	CFV_WORD,				/* b */
	CFV_WORD,				/* c */
	CFV_WORD,				/* d */
	CFV_WORD,				/* e */
	CFV_WORD,				/* f */
	CFV_WORD,				/* g */
	CFV_WORD,				/* h */
	CFV_WORD,				/* i */
	CFV_WORD,				/* j */
	CFV_WORD,				/* k */
	CFV_WORD,				/* l */
	CFV_WORD,				/* m */
	CFV_WORD,				/* n */
	CFV_WORD,				/* o */
	CFV_WORD,				/* p */
	CFV_WORD,				/* q */
	CFV_WORD,				/* r */
	CFV_WORD,				/* s */
	CFV_WORD,				/* t */
	CFV_WORD,				/* u */
	CFV_WORD,				/* v */
	CFV_WORD,				/* w */
	CFV_WORD,				/* x */
	CFV_WORD,				/* y */
	CFV_WORD,				/* z */
	CFV_WORD,				/* { */
	CFV_META | CFV_BREAK,	/*  |  */
	CFV_WORD,				/* } */
	CFV_WORD,				/* ~ */
	CFV_SPECIAL,			/* CTLNUL */
	CFV_WORD,				/* 128 */
	CFV_WORD,				/* 129 */
	CFV_WORD,				/* 130 */
	CFV_WORD,				/* 131 */
	CFV_WORD,				/* 132 */
	CFV_WORD,				/* 133 */
	CFV_WORD,				/* 134 */
	CFV_WORD,				/* 135 */
	CFV_WORD,				/* 136 */
	CFV_WORD,				/* 137 */
	CFV_WORD,				/* 138 */
	CFV_WORD,				/* 139 */
	CFV_WORD,				/* 140 */
	CFV_WORD,				/* 141 */
	CFV_WORD,				/* 142 */
	CFV_WORD,				/* 143 */
	CFV_WORD,				/* 144 */
	CFV_WORD,				/* 145 */
	CFV_WORD,				/* 146 */
	CFV_WORD,				/* 147 */
	CFV_WORD,				/* 148 */
	CFV_WORD,				/* 149 */
	CFV_WORD,				/* 150 */
	CFV_WORD,				/* 151 */
	CFV_WORD,				/* 152 */
	CFV_WORD,				/* 153 */
	CFV_WORD,				/* 154 */
	CFV_WORD,				/* 155 */
	CFV_WORD,				/* 156 */
	CFV_WORD,				/* 157 */
	CFV_WORD,				/* 158 */
	CFV_WORD,				/* 159 */
	CFV_WORD,				/* 160 */
	CFV_WORD,				/* 161 */
	CFV_WORD,				/* 162 */
	CFV_WORD,				/* 163 */
	CFV_WORD,				/* 164 */
	CFV_WORD,				/* 165 */
	CFV_WORD,				/* 166 */
	CFV_WORD,				/* 167 */
	CFV_WORD,				/* 168 */
	CFV_WORD,				/* 169 */
	CFV_WORD,				/* 170 */
	CFV_WORD,				/* 171 */
	CFV_WORD,				/* 172 */
	CFV_WORD,				/* 173 */
	CFV_WORD,				/* 174 */
	CFV_WORD,				/* 175 */
	CFV_WORD,				/* 176 */
	CFV_WORD,				/* 177 */
	CFV_WORD,				/* 178 */
	CFV_WORD,				/* 179 */
	CFV_WORD,				/* 180 */
	CFV_WORD,				/* 181 */
	CFV_WORD,				/* 182 */
	CFV_WORD,				/* 183 */
	CFV_WORD,				/* 184 */
	CFV_WORD,				/* 185 */
	CFV_WORD,				/* 186 */
	CFV_WORD,				/* 187 */
	CFV_WORD,				/* 188 */
	CFV_WORD,				/* 189 */
	CFV_WORD,				/* 190 */
	CFV_WORD,				/* 191 */
	CFV_WORD,				/* 192 */
	CFV_WORD,				/* 193 */
	CFV_WORD,				/* 194 */
	CFV_WORD,				/* 195 */
	CFV_WORD,				/* 196 */
	CFV_WORD,				/* 197 */
	CFV_WORD,				/* 198 */
	CFV_WORD,				/* 199 */
	CFV_WORD,				/* 200 */
	CFV_WORD,				/* 201 */
	CFV_WORD,				/* 202 */
	CFV_WORD,				/* 203 */
	CFV_WORD,				/* 204 */
	CFV_WORD,				/* 205 */
	CFV_WORD,				/* 206 */
	CFV_WORD,				/* 207 */
	CFV_WORD,				/* 208 */
	CFV_WORD,				/* 209 */
	CFV_WORD,				/* 210 */
	CFV_WORD,				/* 211 */
	CFV_WORD,				/* 212 */
	CFV_WORD,				/* 213 */
	CFV_WORD,				/* 214 */
	CFV_WORD,				/* 215 */
	CFV_WORD,				/* 216 */
	CFV_WORD,				/* 217 */
	CFV_WORD,				/* 218 */
	CFV_WORD,				/* 219 */
	CFV_WORD,				/* 220 */
	CFV_WORD,				/* 221 */
	CFV_WORD,				/* 222 */
	CFV_WORD,				/* 223 */
	CFV_WORD,				/* 224 */
	CFV_WORD,				/* 225 */
	CFV_WORD,				/* 226 */
	CFV_WORD,				/* 227 */
	CFV_WORD,				/* 228 */
	CFV_WORD,				/* 229 */
	CFV_WORD,				/* 230 */
	CFV_WORD,				/* 231 */
	CFV_WORD,				/* 232 */
	CFV_WORD,				/* 233 */
	CFV_WORD,				/* 234 */
	CFV_WORD,				/* 235 */
	CFV_WORD,				/* 236 */
	CFV_WORD,				/* 237 */
	CFV_WORD,				/* 238 */
	CFV_WORD,				/* 239 */
	CFV_WORD,				/* 240 */
	CFV_WORD,				/* 241 */
	CFV_WORD,				/* 242 */
	CFV_WORD,				/* 243 */
	CFV_WORD,				/* 244 */
	CFV_WORD,				/* 245 */
	CFV_WORD,				/* 246 */
	CFV_WORD,				/* 247 */
	CFV_WORD,				/* 248 */
	CFV_WORD,				/* 249 */
	CFV_WORD,				/* 250 */
	CFV_WORD,				/* 251 */
	CFV_WORD,				/* 252 */
	CFV_WORD,				/* 253 */
	CFV_WORD,				/* 254 */
	CFV_WORD,				/* 255 */
};

t_char_flags	get_char_flags(int c)
{
	return (g_syn_table[(unsigned char)c]);
}

static int	_get_condition(const uint32_t table[8], int c)
{
	const size_t	arr_index = ((unsigned char)c) >> 5;
	const int		bit_index = ((unsigned char)c) & 0x1f;

	return (table[arr_index] & (1U << bit_index));
}

int	legal_variable_starter(int c)
{
	return (_get_condition(g_legal_variable_starter, c));
}

int	legal_variable_char(int c)
{
	return (_get_condition(g_legal_variable_char, c));
}
