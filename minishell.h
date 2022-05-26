/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:36:15 by jkong             #+#    #+#             */
/*   Updated: 2022/05/26 18:12:18 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

enum	e_char_flag_index
{
	CF_META,
	CF_BREAK,
	CF_QUOTE,
	CF_SPECIAL,
	CF_EXPANSION,
	CF_GLOB,
	CF_BLANK,
};

typedef enum e_char_flag
{
	CFV_WORD = 0,
	CFV_META = 1 << CF_META,
	CFV_BREAK = 1 << CF_BREAK,
	CFV_QUOTE = 1 << CF_QUOTE,
	CFV_SPECIAL = 1 << CF_SPECIAL,
	CFV_EXPANSION = 1 << CF_EXPANSION,
	CFV_GLOB = 1 << CF_GLOB,
	CFV_BLANK = 1 << CF_BLANK,
}	t_char_flags;

typedef enum e_token_kind
{
	TK_EOF = 0,
	TK_PAREN_L = '(',
	TK_PAREN_R = ')',
	TK_LESS = '<',
	TK_GREATER = '>',
	TK_OR = '|',
	TK_AGAIN = 256,
	TK_ERROR,
	TK_UNDEFINED,
	TK_WORD,
	TK_NUMBER,
	TK_LESS_LESS,
	TK_GREATER_GREATER,
	TK_AND_AND,
	TK_OR_OR,
}	t_token_kind;

enum	e_word_flag_index
{
	WF_WANT_EXPAND_VAR,
	WF_WANT_DEQUOTE,
	WF_NO_GLOB,
};

typedef int							t_word_flags;

typedef struct s_word
{
	char			*str;
	t_word_flags	flags;
}	t_word;

typedef struct s_list_word
{
	struct s_list_word	*next;
	t_word				word;
}	t_list_word;

typedef struct s_redirect
{
	t_word	word;
}	t_redirect;

typedef struct s_list_redirect
{
	struct s_list_redirect	*next;
	t_redirect				redirect;
}	t_list_redirect;

/**
 * BEGIN Command
 */
typedef enum e_command_type
{
	CMD_NOOP,
	CMD_CONNECTION,
	CMD_SIMPLE,
	CMD_SUBSHELL,
}	t_command_type;

enum e_command_flag_index
{
	CMDF_NOOP,
};

typedef int							t_command_flags;

typedef struct s_command_connection	t_command_connection;
typedef struct s_simple_command		t_simple_command;
typedef struct s_subshell_command	t_subshell_command;

union u_command_variant
{
	t_command_connection	*connection;
	t_simple_command		*simple;
	t_subshell_command		*subshell;
};

typedef struct s_command_container
{
	t_command_type			type;
	union u_command_variant	value;
}	t_command_container;

struct s_command_connection
{
	t_token_kind		connector;
	t_command_type		flags;
	t_command_container	*first;
	t_command_container	*second;
};

struct s_simple_command
{
	t_command_type	flags;
	t_list_word		*word_list;
	t_list_redirect	*redirect_list;
};

struct s_subshell_command
{
	t_command_type		flags;
	t_command_container	*container;
};
/**
 * END Command
 */

enum	e_parser_flag_index
{
	PF_WANT_REDIRECT,
	PF_SUBSHELL,
	PF_SUBSTITUTION,
	PF_HERE_DOCUMENT,
	PF_COMMAND_PUSHED,
	PF_REDIRECT_PUSHED,
};

typedef int							t_parser_flags;

typedef struct s_parse_stack
{

}	t_parse_stack;

typedef struct s_parse_state
{
	char					*begin;
	char					*str;
	t_parser_flags			flags;
	t_parse_stack			initial_stack[200];
	t_parse_stack			*stack_ptr;
	t_word					now_word;
	t_redirect				now_redirect;
	t_command_container		*now_command;
	t_command_container		*command;
}	t_parse_state;

t_char_flags	get_char_flags(int c);
t_token_kind	read_token(t_parse_state *pst);
void			lex(t_parse_state *pst);

#endif
