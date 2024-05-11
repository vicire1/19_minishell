NAME			= minishell

SRC_MANDATORY	= 	src/main.c \
					src/lexer/lexer.c \
					src/utils/utils_lexer.c \
					src/utils/utils_libft.c \

OBJ_MANDATORY	= ${SRC_MANDATORY:.c=.o}

# MINI_LIBFT		= mini_libft.a

# MINI_LIBFT_PATH	= mini_libft

PRINTF_PATH		= Printf_fd

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