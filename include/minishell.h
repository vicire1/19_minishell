/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:08:02 by vdecleir          #+#    #+#             */
/*   Updated: 2024/06/10 16:22:33 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include "../mini_libft/includes/ft_printf.h"
// # include "../mini_libft/includes/get_next_line.h"
// # include "../mini_libft/includes/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../ft_printf_fd/ft_printf.h"

// DEFINE

# define ERR_MAL "Memory alloction failed."
# define ERR_SYN "Syntax error."

// LEXER STRUCT

typedef enum s_token
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}			t_token;

typedef struct s_redir
{
	t_token	token;
	char	*file;
	void	*next;
}				t_redir;

typedef struct	s_pars
{
	char	**cmd;
	int		nb_redir;
	t_redir	*redir;
	void	*next;
	void	*prev;
}				t_pars;

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
	t_pars	*first_pars;
}   t_data;

//src/lexer
int lexer(char *line, t_data *data);

//parser
int	parser(t_data *data);
void	add_redir_to_pars(t_pars *first_pars, t_redir *first_redir);
t_redir	*init_redir_node(t_data *data, t_lexer *file_node, int token, int i);
int	new_node_pars(t_data *data, t_lexer *start, int arg, int redir);
char	**create_cmd(t_data *data, t_lexer *start, int arg);
int free_all(t_data *data, char *str, int esc);

//src/utils
int		free_lex(t_data *data);
char	*ft_substr(char const *s, unsigned int start, size_t len, t_data *data);
size_t	ft_strlen(const char *str);
int		is_white_space(char c);
char	*ft_strdup(const char *s);


#endif