/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:08:02 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/07 15:08:51 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../mini_libft/includes/ft_printf.h"
# include "../mini_libft/includes/get_next_line.h"
# include "../mini_libft/includes/libft.h"

// LEXER STRUCT

typedef enum s_token
{
	PIPE,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_token;

typedef struct  s_lexer
{
    void    *prev;
    void    *next;
    int     pos;
    char    *token_str;
    t_token token;
}               t_lexer;


#endif