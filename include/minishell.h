/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:08:02 by vdecleir          #+#    #+#             */
/*   Updated: 2024/06/07 12:35:19 by lbirloue         ###   ########.fr       */
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

#include "libc.h"
#include "string.h"

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

typedef struct s_expander
{
	int	l_s_quotes;
	int	l_db_quotes;
	int	r_s_quotes;
	int	r_db_quotes;
}			t_expander;


typedef struct s_lexer
{
	int		pos;
	char	*token_str;
	t_token	token;
	void	*next;
	void	*prev;
}			t_lexer;

typedef struct s_env
{
	char	*env_str;
	void	*next;
	void	*prev;
}			t_env;

typedef struct s_data
{
	t_expander	*expand;
	t_lexer	*first;
	t_env	*first_env;
	int		pos;
}t_data;


//src/expand
int expander(t_data *data);

//src/expand_quotes
int	check_quotes(t_lexer *exp, int j, int i);


//src/parser
int	parser( t_data *data);

//src/lexer
int lexer(char *line, t_data *data);

//src/utils
int		free_all(t_data *data, char *str, int esc);
char	*ft_substr(char const *s, unsigned int start, size_t len, t_data *data);
size_t	ft_strlen(const char *str);
int	ft_isalnum(int c);
int		is_white_space(char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);


//src/utils/utils_expand
int	size_env_doll(char *str);
int	size_env_value(char *env_line);
int	size_env_name(char *env_line);
int	check_v_env(char *str);
int	env_cmp(char *str, char *str_env);

//src/utils/utils_env
void	print_env(t_data *data);
int		new_node_env(char *str, t_data *data);

#endif


/*

test"$USER"'$USER'$USER"test"$non
testlbirloue$USERlbirlouetest

*/