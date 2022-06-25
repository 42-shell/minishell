/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:36:15 by jkong             #+#    #+#             */
/*   Updated: 2022/06/25 12:50:02 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <stdlib.h>
# include <stddef.h>
# include <signal.h>

extern sig_atomic_t					g_exit_status;

# define HERE_DOCUMENT_MAX 16
# define NO_PIPE (-1)

# define EX_BADUSAGE 2

# define EX_NOEXEC 126
# define EX_NOTFOUND 127

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
	WF_HAS_DOLLAR,
	WF_SPLIT,
	WF_PARAM,
	WF_IFS,
};

typedef enum e_word_flags
{
	WFV_HAS_DOLLAR = 1 << WF_HAS_DOLLAR,
	WFV_SPLIT = 1 << WF_SPLIT,
	WFV_PARAM = 1 << WF_PARAM,
	WFV_IFS = 1 << WF_IFS,
	WFV_NOQUOTE = WFV_HAS_DOLLAR | WFV_SPLIT,
	WFV_DBLQUOTE = WFV_HAS_DOLLAR,
}	t_word_flags;

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
	CMDF_ASYNC,
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
	PF_HERE_DOCUMENT,
};

# define PARSER_ACCEPT -1000
# define PARSER_ERROR -1001

typedef int							t_parser_state;
typedef int							t_parser_flags;

typedef enum e_parser_error
{
	PE_SUCCESS,
	PE_AGAIN,
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
	t_list_redirect			*here_document[HERE_DOCUMENT_MAX];
	size_t					here_document_index;
}	t_parser;

typedef struct s_state_info
{
	t_token_kind			token;
	t_parser_state			state;
}	t_state_info;

typedef t_token_kind				t_parse_func(t_parser *);

typedef struct s_list_process
{
	struct s_list_process	*next;
	pid_t					pid;
}	t_list_process;

enum	e_var_flag_index
{
	VF_EXPORTED,
};

typedef enum e_var_flag
{
	VFV_EXPORTED = 1 << VF_EXPORTED,
}	t_var_flags;

enum	e_file_flag_index
{
	FF_DIRECTORY,
	FF_HIDDEN,
};

typedef int							t_file_flags;

typedef struct s_list_var
{
	struct s_list_var	*next;
	char				*name;
	char				*value;
	t_var_flags			attr;
}	t_list_var;

typedef struct s_shell
{
	int				next_pipe;
	int				redir_undo[3];
	t_list_process	*pid_list;
	t_list_var		*var_list;
}	t_shell;

typedef struct s_str_buf			t_str_buf;
typedef struct s_str_vec			t_str_vec;

void					print_err(const char *format, ...);
void					exit_fail(const char *s);

t_char_flags			char_flags(int c);
size_t					next_syntax(char *s, t_char_flags flag);
int						legal_variable_starter(int c);
int						legal_variable_char(int c);
t_token_kind			read_token(t_parser *pst);
int						parse(t_parser *pst);

void					parser_stack_reserve(t_parser *pst, size_t n);
void					parser_stack_remove_all(t_parser *pst);
t_parser_state			parser_state(t_parser_state state, t_token_kind token);

t_simple_command		*make_simple_command(void);
t_subshell_command		*make_subshell(t_command *container);
t_command_connection	*connect_command(t_command *lhs, t_command *rhs,
							t_token_kind connector);
void					append_word(t_list_word **list, t_word *item);
void					combine_simple_command(t_simple_command *lhs,
							t_simple_command *rhs);

void					set_redirect(t_redirect *item, int src,
							t_redirection ins, t_word *dest);
t_list_redirect			*append_redirect(t_list_redirect **list,
							t_redirect *item);
void					subshell_apply_redirect(t_subshell_command *subshell,
							t_list_redirect *r_list);

void					dispose_word(t_word *item);
void					dispose_redirect(t_redirect *item);
void					dispose_command(t_command *item);

void					push_here_document(t_parser *pst, t_list_redirect *r);
int						gather_here_document(t_parser *pst);
char					*read_document(char *eof);
char					*read_document_pipe(char *eof);

char					*get_token_str(t_token_kind token);
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

char					*get_ifs(t_list_var *v_list);

int						get_exit_status(int status);

int						execute_command(t_shell *sh, t_command *cmd,
							int pipe_in, int pipe_out);
int						execute_simple_command(t_shell *sh, t_command *cmd,
							int pipe_in, int pipe_out);
int						execute_pipeline(t_shell *sh, t_command *cmd,
							int pipe_in, int pipe_out);

void					do_piping(int pipe_in, int pipe_out, int pipe_next);
pid_t					make_child(t_shell *sh);
int						wait_for(t_shell *sh, pid_t pid);

int						do_redirections(t_list_redirect *r_list, t_shell *sh);
void					add_undo_redirects(t_shell *sh);
void					cleanup_redirects(t_shell *sh);

char					*get_var(t_list_var *list, char *name, int dup);
void					put_var(t_list_var **list_ptr, char *name, char *value,
							t_var_flags attr);
void					unset_var(t_list_var **list_ptr, char *name);

char					*alloc_str_pair(const char *s, char **val_ptr,
							char delim);
t_list_var				*strvec_to_var_list(char **arr);
char					**var_list_to_strvec(t_list_var *list);
void					dispose_var_list(t_list_var *list);

t_list_var				*clone_var_list(t_list_var *list);
t_list_var				*sort_var_list(t_list_var *list);

void					append_word_list(t_list_word **list_ptr, char *str,
							t_word_flags flags);
void					delete_word_list(t_list_word *list);
void					singleton_word_list(t_list_word *ptr, t_word *word);

char					*find_command(t_shell *sh, char *name);
char					**glob_to_strvec(const char *path, const char *pattern);

t_list_word				*expand_map(t_list_word *w_list, t_list_var *v_list,
							int mode);
char					**expand_collect(t_list_word *w_list, char *path);
char					*expand_collect_standalone(t_list_word *w_list);

char					**word_expand(t_shell *sh, t_list_word *w_list);
char					*redir_expand(t_shell *sh, t_word *word);
void					heredoc_eof_expand(t_word *word);
char					*heredoc_expand(t_shell *sh, t_word *word,
							size_t *len_ptr);

void					set_signal_handler(int state);
void					on_signal(void);

#endif
