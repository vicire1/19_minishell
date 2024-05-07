# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 15:54:36 by lbirloue          #+#    #+#              #
#    Updated: 2024/03/25 08:03:02 by lbirloue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

INCLUDES		=	-I.

OBJ_DIR			=	objects

SRCS_LIBFT		=	srcs_libft/ft_atoi.c \
					srcs_libft/ft_isascii.c \
					srcs_libft/ft_isalpha.c \
					srcs_libft/ft_isdigit.c \
					srcs_libft/ft_isprint.c \
					srcs_libft/ft_memchr.c \
					srcs_libft/ft_memcmp.c \
					srcs_libft/ft_memcpy.c \
					srcs_libft/ft_memmove.c \
					srcs_libft/ft_memset.c \
					srcs_libft/ft_strchr.c \
					srcs_libft/ft_strdup.c \
					srcs_libft/ft_strlcat.c \
					srcs_libft/ft_strlcpy.c \
					srcs_libft/ft_strlen.c \
					srcs_libft/ft_strncmp.c \
					srcs_libft/ft_strnstr.c \
					srcs_libft/ft_strrchr.c \
					srcs_libft/ft_tolower.c \
					srcs_libft/ft_toupper.c \
					srcs_libft/ft_substr.c \
					srcs_libft/ft_strjoin.c \
					srcs_libft/ft_split.c \
					srcs_libft/ft_itoa.c \
					srcs_libft/ft_striteri.c \
					srcs_libft/ft_putchar_fd.c \
					srcs_libft/ft_putstr_fd.c \
					srcs_libft/ft_putendl_fd.c \
					srcs_libft/ft_putnbr_fd.c \

SRCS_PRINTF		=	srcs_ft_printf/flags.c \
					srcs_ft_printf/utils_ft_printf.c \
					srcs_ft_printf/flag_X.c \
					srcs_ft_printf/flag_xx.c \
					srcs_ft_printf/flag_di.c \
					srcs_ft_printf/flag_u.c \
					srcs_ft_printf/flag_p.c \
					srcs_ft_printf/counters.c \
					srcs_ft_printf/ft_printf.c \

SRCS_GNL		=	srcs_gnl/get_next_line_utils.c \
					srcs_gnl/get_next_line.c \

OBJS			=	$(SRCS_LIBFT:.c=.o) $(SRCS_PRINTF:.c=.o) $(SRCS_GNL:.c=.o)

LIBRARY			=	mini_libft.a

all: $(LIBRARY)
	@echo "\033[38;5;208mmini_libft compilation\033[0m\c"
	@sleep 1
	@echo "\033[38;5;208m.\033[0m\c"
	@sleep 1
	@echo "\033[38;5;208m.\033[0m\c"
	@sleep 1
	@echo "\033[38;5;208m.\n\033[0m\c"
	@sleep 1
	@tput cuu1; tput el
	@sleep 0.5
	@echo "\033[38;5;40mmini_libft compiled\033[0m"

$(LIBRARY): $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIBRARY)

re: fclean all

.PHONY: all clean fclean re