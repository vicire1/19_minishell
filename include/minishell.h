/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:08:02 by vdecleir          #+#    #+#             */
/*   Updated: 2024/07/03 14:03:22 by lbirloue         ###   ########.fr       */
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
# include <sys/stat.h>
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
	int		val_len;
	int		n_len;
	char	*tmp_val;
	char	*tmp;
	char	*first_part;
	char	*sec_part;
	char	*third_part;
}			t_expander;


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

typedef struct s_env
{
	char	*name;
	char	*value;
	int		env_status; //1=> dans env et export/ 0=> dans export mais pas env
	void	*next;
	void	*prev;
}			t_env;

typedef struct s_data
{
	t_expander	*expa;
	t_lexer	*first_lex;
	t_env	*first_env;
	t_pars	*first_pars;
	int		pos;
}t_data;


//src/expand
int		in_env(t_data *data, t_env *env, char *str, t_expander *expa);
int		expander(t_data *data);

//src/expand_quotes
int	delete_quotes(t_data *data, t_lexer *exp);
int	check_quotes_single(t_lexer *exp, int j, int i);
int	check_quotes_db(char *str, int j, int i);
int	check_quotes(t_lexer *exp, int j, int i);

//src/expand_env
void	replace_env(t_data *data, t_lexer *exp, int j, t_expander *expa);

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
char	*ft_substr(char const *s, unsigned int start, size_t len, t_data *data);
char	*ft_substr_bis(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		is_white_space(char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s, t_data *data);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2, t_data *data);
char	*ft_strjoin_bis(char const *s1, char const *s2);


//src/utils/utils_expand
int	size_env_doll(char *str);
int	size_env_value(char *env_line);
int	size_env_name(char *env_line);
int	check_v_env(char *str);
void	free_two(void *first, void *sec);
int	env_cmp(char *str, char *str_env);

//src/utils/utils_free
void	free_env(t_data *data);
void	free_two(void *first, void *sec);
void    free_pars(t_data *data);
int		free_lex(t_data *data);

//src/utils/utils_env
void	print_env(t_data *data);
void	init_export(t_data *data);
char	*get_name_env(char *str, t_data *data);
char 	*get_value_env(char *str, t_data *data);
int		new_node_env(char *str,int status, t_data *data);
int	new_node_env_w_data(char *val, char *name, int status, t_data *data);


//BUILTINS
//sec/buitins/pwd.c
void	cmd_pwd(t_data *data, int fd);

//sec/buitins/env.c
void	cmd_env(t_data *data, char **str, int fd);

//sec/buitins/export.c
void	cmd_export(t_data *data, char **str, int fd);

//sec/buitins/cd.c
void	cmd_cd(t_data *data, char **str, int fd);

//sec/buitins/unset.c
int		cmd_unset_check_invalid(char *str);
void	cmd_unset_do_it(t_data *data, char *str);
void	cmd_unset_do_it_sec(t_data *data, char *str);
void	cmd_unset(t_data *data, char **str, int fd);

//sec/buitins/echo.c
void    cmd_echo(t_data *data, char **str, int fd);

//sec/buitins/buitlin.c
int		check_if_builtin(char *str);
void	dispatch_builtins(t_data *data, char **str, int fd, int which);


#endif


/*

test"$USER"'$USER'$USER"test"$non$
testlbirloue$USERlbirlouetest$

*/