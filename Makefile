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

OBJECTS_DIR = objs/

HEADER = minishell.h
SOURCE = shell.c \
			syntax.c lexer.c parser.c \
			parser_state.c parser_utils.c \
			parser_reduce_0.c parser_reduce_1.c \
			parser_reduce_2.c parser_reduce_3.c \
			make_command.c make_command_redir.c dispose_command.c \
			execute_command.c execute_command_pipeline.c \
			execute_command_redir.c execute_command_redir_undo.c \
			execute_command_jobs.c \
			expander.c here_document.c \
			minishell_utils.c env_module_1.c env_module_2.c env_module_3.c \
			env_module_util_list.c \
			built_in_cd.c built_in_echo.c built_in_env.c built_in_exit.c \
			built_in_export.c built_in_pwd.c built_in_unset.c built_in.c \
			expander_util.c glob_init.c glob_workhorse.c glob_workhorse_shoe.c
OBJECT = $(addprefix $(OBJECTS_DIR), $(SOURCE:.c=.o))

HEADER_LIBFT = libft.h
SOURCE_LIBFT = libft_memory.c libft_string.c libft_string_search.c \
			libft_split.c libft_stdlib.c
OBJECT_LIBFT = $(addprefix $(OBJECTS_DIR), $(SOURCE_LIBFT:.c=.o))

SOURCE_GENERAL = util_flag.c safe_io.c safe_io_utils.c safe_mem.c \
					string_buffer.c string_vector.c string_vector_utils.c \
					generic_list.c
OBJECT_GENERAL = $(addprefix $(OBJECTS_DIR), $(SOURCE_GENERAL:.c=.o))

TARGET = minishell
OBJS = $(OBJECT) $(OBJECT_LIBFT) $(OBJECT_GENERAL)

LDFLAGS += -lreadline

C_SANITIZER_FLAGS = address undefined
CFLAGS += $(addprefix -fsanitize=, $(C_SANITIZER_FLAGS))
LDFLAGS += $(addprefix -fsanitize=, $(C_SANITIZER_FLAGS))

C_WARNING_FLAGS = all extra error
CFLAGS += $(addprefix -W, $(C_WARNING_FLAGS))

C_DEBUG_FLAGS = g3
CFLAGS += $(addprefix -, $(C_DEBUG_FLAGS))

all: $(TARGET)
clean:				;	$(RM) -r $(OBJECTS_DIR)
fclean: clean		;	$(RM) $(TARGET)
re: fclean			;	make all

$(OBJECTS_DIR):
	mkdir $(OBJECTS_DIR)

$(OBJS): | $(OBJECTS_DIR)

$(addprefix $(OBJECTS_DIR), %.o): %.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(SOURCE): $(HEADER)

$(SOURCE_LIBFT): $(HEADER_LIBFT)

$(addprefix $(OBJECTS_DIR), util_flag.o): util_flag.h
$(addprefix $(OBJECTS_DIR), safe_io.o safe_io_utils.o): safe_io.h
$(addprefix $(OBJECTS_DIR), safe_mem.o): safe_mem.h
$(addprefix $(OBJECTS_DIR), string_buffer.o): string_buffer.h
$(addprefix $(OBJECTS_DIR), string_vector.o string_vector_utils.o): string_vector.h
$(addprefix $(OBJECTS_DIR), generic_list.o): generic_list.h
