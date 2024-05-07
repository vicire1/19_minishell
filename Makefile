NAME			= minishell

SRC_MANDATORY	= 	src/main.c \
					src/lexer/lexer.c \
					src/utils/utils_lexer.c

OBJ_MANDATORY	= ${SRC_MANDATORY:.c=.o}

MINI_LIBFT		= mini_libft.a

MINI_LIBFT_PATH	= mini_libft

CC				= cc

RM				= rm -rf

# C_FLAGS			= -Wall -Wextra -Werror

LIBS			= -lreadline

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@ 

all: ${NAME}
${NAME}: ${OBJ_MANDATORY} ${MINI_LIBFT}
	${CC} ${OBJ_MANDATORY} -o ${NAME} ${MINI_LIBFT} ${LIBS}

${MINI_LIBFT}:
	${MAKE} -C ${MINI_LIBFT_PATH} 
	mv ${MINI_LIBFT_PATH}/${MINI_LIBFT} .

clean:
	${MAKE} clean -C ${MINI_LIBFT_PATH} 
	${RM} ${OBJ_MANDATORY}
	${RM} ${FT_PRINTF} 

fclean: clean
	${RM} ${NAME} ${MINI_LIBFT} 

re: fclean all

.PHONY: all bonus clean fclean re