/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:08:02 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/08 00:40:52 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../mini_libft/includes/ft_printf.h"
# include "../mini_libft/includes/get_next_line.h"
# include "../mini_libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

// LEXER STRUCT

typedef enum s_token
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}			t_token;

typedef struct s_lexer
{
	int		pos;
	char	*token_str;
	t_token	token;
	void	*next;
	void	*prev;
}			t_lexer;

typedef struct s_data
{
    t_lexer *first;
}   t_data;



//srcs/lexer/lexer.c
int lexer(char *line, t_data *data);

//srcs/utils
void free_all(t_data *data, char *str);

#endif