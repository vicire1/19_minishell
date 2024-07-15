NAME			= minishell

SRC_MANDATORY	= 	src/main.c \
					src/lexer/lexer.c \
					src/expand/expand.c \
					src/expand/expand_env.c \
					src/expand/expand_quotes.c \
					src/expand/utils_env.c \
					src/expand/utils_expander.c \
					src/parser/parser.c \
					src/parser/parser_node.c \
					src/builtins/pwd.c \
					src/builtins/env.c \
					src/builtins/export.c \
					src/builtins/cd.c \
					src/builtins/unset.c \
					src/builtins/echo.c \
					src/builtins/exit.c \
					src/builtins/builtin.c \
					src/utils/utils_libft.c \
					src/utils/utils_free.c \
					src/utils/free_lex_pars.c \
					src/exec/get_env.c \
					src/exec/redirections.c \
					src/exec/exec.c \

OBJ_MANDATORY	= ${SRC_MANDATORY:.c=.o}

# MINI_LIBFT		= mini_libft.a

# MINI_LIBFT_PATH	= mini_libft

PRINTF_PATH		= ft_printf_fd

PRINTF			= libftprinf.a

CC				= cc

RM				= rm -rf

C_FLAGS			= -Wall -Wextra -Werror

LIBS			= -lreadline

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@ 

all: ${PRINTF} ${NAME}

${NAME}: ${OBJ_MANDATORY}
	${CC} ${OBJ_MANDATORY} -L${PRINTF_PATH} -lftprintf -o ${NAME} ${LIBS}

${PRINTF}:
	${MAKE} -C ${PRINTF_PATH}

clean:
	${MAKE} clean -C ${PRINTF_PATH}
	${RM} ${OBJ_MANDATORY}
	${RM} ${PRINTF}

fclean: clean
	${MAKE} fclean -C ${PRINTF_PATH}
	${RM} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re
