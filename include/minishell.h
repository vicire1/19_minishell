/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:08:02 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/07 17:03:34 by lbirloue         ###   ########.fr       */
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
	PIPE,
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
}			t_lexer;

typedef struct s_data
{
    t_lexer **lexer;
    int     lexer_nb;


}   t_data;



//srcs/lexer/lexer.c
int lexer(t_data *data);

#endif