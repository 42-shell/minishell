# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 18:42:42 by jkong             #+#    #+#              #
#    Updated: 2022/05/20 18:42:42 by jkong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES: .c .o .h
.PHONY: all clean fclean re

CC = cc
RM = rm -f

TARGET = minishell
OBJECTS_DIR = objs/

# Entrypoint
SOURCES += shell.c

# minishell Private
SOURCES += minishell_utils.c

# Parser
SOURCES += syntax.c \
			lexer.c \
			parser.c \
			parser_state.c \
			parser_utils.c \
			parser_reduce_0.c \
			parser_reduce_1.c \
			parser_reduce_2.c \
			parser_reduce_3.c

# Shell implements
SOURCES += make_command.c \
			make_command_redir.c \
			dispose_command.c \
			execute_command.c \
			execute_command_pipeline.c \
			execute_command_redir.c \
			execute_command_redir_undo.c \
			execute_command_simple.c \
			execute_command_jobs.c \
			here_document.c \
			here_document_pipe.c \
			finder.c \
			glob.c \
			variables.c \
			variables_utils.c \
			variables_utils_sort.c \
			word_list.c \
			expander.c \
			expander_tear.c \
			expander_fuse.c \
			signals.c

# Shell built-ins
SOURCES += builtin_echo.c \
			builtin_cd.c \
			builtin_pwd.c \
			builtin_export.c \
			builtin_unset.c \
			builtin_env.c \
			builtin_exit.c \
			builtins.c

# LibFT
SOURCES += libft_memory.c \
			libft_string.c

# Utilities
SOURCES += util_flag.c \
			safe_io.c \
			safe_io_utils.c \
			safe_mem.c \
			string_buffer.c \
			string_buffer_utils.c \
			string_vector.c \
			string_vector_utils.c \
			generic_list.c \
			util_try_atoi.c

OBJECTS = $(addprefix $(OBJECTS_DIR), $(SOURCES:.c=.o))

C_WARNING_FLAGS = all extra error
CFLAGS += $(addprefix -W, $(C_WARNING_FLAGS))

READLINE_PATH = ..
INCLUDE += -I$(READLINE_PATH)
LDFLAGS += -L$(READLINE_PATH)/readline -lreadline -lhistory -lncurses

ifdef DEBUG
	C_SANITIZER_FLAGS += $(SANITIZE)
	CFLAGS += $(addprefix -fsanitize=, $(C_SANITIZER_FLAGS))
	LDFLAGS += $(addprefix -fsanitize=, $(C_SANITIZER_FLAGS))
	C_CONFIG_FLAGS += g3 O0
endif

CFLAGS += $(addprefix -, $(C_CONFIG_FLAGS))

all: $(TARGET)
clean:				;	$(RM) -r $(OBJECTS_DIR)
fclean: clean		;	$(RM) $(TARGET)
re: fclean			;	$(MAKE) all

$(OBJECTS_DIR):
	mkdir $(OBJECTS_DIR)

$(OBJECTS_DIR)%.o: %.c | $(OBJECTS_DIR)
	$(CC) $(INCLUDE) -c $< -o $@ $(CFLAGS) -MMD -MF $(@:.o=.d) -MT $@ -MP

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

-include $(OBJECTS:.o=.d)
