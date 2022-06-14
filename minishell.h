/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:36:15 by jkong             #+#    #+#             */
/*   Updated: 2022/06/14 17:02:36 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stddef.h>

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
	TK_LESS_LESS,
	TK_GREATER_GREATER,
	TK_AND_AND,
	TK_OR_OR,
	TK_NT_ACCEPT = 512,
	TK_NT_SIMPLE_COMMAND_ELEMENT,
	TK_NT_REDIRECTION,
	TK_NT_SIMPLE_COMMAND,
	TK_NT_REDIRECTION_LIST,
	TK_NT_COMMAND,
	TK_NT_SUBSHELL,
	TK_NT_LIST,
	TK_NT_PIPELINE,
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

typedef enum e_redirection
{
	R_NONE,
	R_OUTPUT_DIRECTION,
	R_INPUT_DIRECTION,
	R_APPENDING_TO,
	R_READING_UNTIL,
}	t_redirection;

typedef struct s_redirect
{
	int				redirectee;
	t_redirection	instruction;
	t_word			word;
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
	void					*ptr;
	t_command_connection	*connection;
	t_simple_command		*simple;
	t_subshell_command		*subshell;
};

typedef struct s_command
{
	t_command_type			type;
	union u_command_variant	value;
}	t_command;

struct s_command_connection
{
	t_command_flags	flags;
	t_token_kind	connector;
	t_command		first;
	t_command		second;
};

struct s_simple_command
{
	t_command_flags	flags;
	t_list_word		*word_list;
	t_list_redirect	*redirect_list;
};

struct s_subshell_command
{
	t_command_flags	flags;
	t_command		container;
	t_list_redirect	*redirect_list;
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

# define PARSER_ACCEPT -1000
# define PARSER_ERROR -1001

typedef int							t_parser_state;
typedef int							t_parser_flags;

typedef enum e_parser_error
{
	PE_SUCCESS,
	PE_INCOMPLETED_PAIR,
	PE_SYNTAX_ERROR,
}	t_parser_error;

typedef struct s_parser_stack
{
	t_parser_state	state;
	t_token_kind	kind;
	t_word			word;
	t_redirect		redirect;
	t_command		command;
}	t_parser_stack;

typedef struct s_parser
{
	char					*begin;
	char					*str;
	t_word					backup_word;
	t_parser_flags			flags;
	t_parser_error			error;
	size_t					stack_capacity;
	t_parser_stack			*stack_base;
	t_parser_stack			*now;
}	t_parser;

typedef struct s_state_info
{
	t_token_kind			token;
	t_parser_state			state;
}	t_state_info;

typedef t_token_kind				t_parse_func(t_parser *);

t_char_flags			get_char_flags(int c);
t_token_kind			read_token(t_parser *pst);
int						parse(t_parser *pst);

t_parser_state			parser_state(t_parser_state state, t_token_kind token);

t_simple_command		*make_simple_command(void);
t_subshell_command		*make_subshell(t_command *container);
t_command_connection	*connect_command(t_command *a, t_command *b,
							t_token_kind c);
void					append_word(t_list_word **list, t_word *item);
void					combine_simple_command(t_simple_command *lhs,
							t_simple_command *rhs);
void					dispose_word(t_word *item);
void					dispose_command(t_command *item);

void					set_redirect(t_redirect *item, int src, t_redirection r,
							t_word *dest);
void					dispose_redirect(t_redirect *item);
void					append_redirect(t_list_redirect **list,
							t_redirect *item);
void					subshell_apply_redirect(t_subshell_command *subshell,
							t_list_redirect *r_list);

void					swap_word(t_word *a, t_word *b);
void					swap_redirect(t_redirect *a, t_redirect *b);
void					swap_command(t_command *a, t_command *b);
void					clear_parser_stack_item(t_parser_stack *item);

t_token_kind			parser_reduce_0(t_parser *pst);
t_token_kind			parser_reduce_1(t_parser *pst);
t_token_kind			parser_reduce_2(t_parser *pst);
t_token_kind			parser_reduce_3(t_parser *pst);
t_token_kind			parser_reduce_4(t_parser *pst);
t_token_kind			parser_reduce_5(t_parser *pst);
t_token_kind			parser_reduce_6(t_parser *pst);
t_token_kind			parser_reduce_7(t_parser *pst);
t_token_kind			parser_reduce_8(t_parser *pst);
t_token_kind			parser_reduce_9(t_parser *pst);
t_token_kind			parser_reduce_10(t_parser *pst);
t_token_kind			parser_reduce_11(t_parser *pst);
t_token_kind			parser_reduce_12(t_parser *pst);
t_token_kind			parser_reduce_13(t_parser *pst);
t_token_kind			parser_reduce_14(t_parser *pst);
t_token_kind			parser_reduce_15(t_parser *pst);
t_token_kind			parser_reduce_16(t_parser *pst);
t_token_kind			parser_reduce_17(t_parser *pst);
t_token_kind			parser_reduce_18(t_parser *pst);
t_token_kind			parser_reduce_19(t_parser *pst);

#endif
