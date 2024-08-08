# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 16:53:35 by vdecleir          #+#    #+#              #
#    Updated: 2024/08/08 16:59:27 by vdecleir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
GREEN_BOLD = \033[1;32m
ORANGE = \033[0;38;5;214m
YELLOW = \033[0;33m
CLOSE = \033[0m

NAME = minishell

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror

RL_LIB	= /Users/$(USER)/.brew/opt/readline/lib

RL_INC	= /Users/$(USER)/.brew/opt/readline/include

LIBS	= -lreadline -L$(RL_LIB) -I$(RL_INC)

SRCS =	src/main.c \
		src/lexer/lexer.c \
		src/expand/expand.c \
		src/expand/expand_env.c \
		src/expand/expand_quotes.c \
		src/expand/utils_env.c \
		src/expand/env_init.c \
		src/expand/utils_expander.c \
		src/expand/utils_expander_sec.c \
		src/parser/parser.c \
		src/parser/parser_node.c \
		src/builtins/pwd.c \
		src/builtins/env.c \
		src/builtins/export/export.c \
		src/builtins/export/export_utils.c \
		src/builtins/export/export_check.c \
		src/builtins/export/export_plus_egal.c \
		src/builtins/cd.c \
		src/builtins/cd_utils.c \
		src/builtins/unset.c \
		src/builtins/unset_utils.c \
		src/builtins/echo.c \
		src/builtins/exit.c \
		src/builtins/exit_utils.c \
		src/builtins/builtin.c \
		src/utils/utils_libft1.c \
		src/utils/utils_libft2.c \
		src/utils/utils_libft3.c \
		src/utils/utils_libft4.c \
		src/utils/utils_free.c \
		src/utils/free_all.c \
		src/exec/get_env.c \
		src/exec/redirections.c \
		src/exec/exec.c \
		src/exec/heredoc.c \
		src/signal.c \

OBJ_DIR = objets

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

PRINTF = libftprintf.a

PRINTF_PATH = ./ft_printf_fd

PRINTF_FLAG = $(PRINTF_PATH)/.libcompiled

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF_FLAG)
	@echo "$(ORANGE)Compiling Minishell...$(CLOSE)"
	@$(CC) $(OBJS)  -L$(PRINTF_PATH) -lftprintf -o $(NAME) $(LIBS)
	@echo "$(GREEN_BOLD)The Minishell executable is ready.$(CLOSE)"

$(PRINTF_FLAG):
	@echo "$(ORANGE)Compiling Ft_printf...$(CLOSE)"
	@make -s -C $(PRINTF_PATH)
	@echo "$(GREEN)Ft_printf ready.$(CLOSE)"
	@touch $(PRINTF_FLAG)

clean:
	@$(MAKE) clean -s -C $(PRINTF_PATH)
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW)Objects correctly deleted.$(CLOSE)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(PRINTF_PATH)/$(PRINTF) $(PRINTF_FLAG)
	@echo "$(YELLOW)Executable file(s) correctly deleted.$(CLOSE)"

re: fclean all

.PHONY: all clean fclean re