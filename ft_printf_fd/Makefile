# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 17:45:41 by vdecleir          #+#    #+#              #
#    Updated: 2023/11/09 14:29:15 by vdecleir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc

NAME 		= libftprintf.a

CFLAGS 		= -Wall -Wextra -Werror

SRCS	 	= 	ft_printf.c \
				printf_di.c \
				ft_strlen.c \
				printf_xXu.c \
				printf_p.c \
				printf_putchar.c \
				printf_putstr.c

INCLUDES	= -I ft_printf.h

OBJECTS	= 	$(SRCS:.c=.o)

RM			= rm -f

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJECTS)
			ar -rcs $(NAME) $(OBJECTS)

all:		$(NAME)


clean:
			$(RM) $(OBJECTS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: 	all clean fclean re