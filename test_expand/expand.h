#ifndef EXPAND_H
# define EXPAND_H

#include "stdio.h"
#include "stdlib.h"
#include "libc.h"

typedef struct s_expand
{
	char **test;
	int	l_s_quotes;
	int	l_db_quotes;
	int	r_s_quotes;
	int	r_db_quotes;

}			t_expand;


int main(int ac, char **av);
void    reset_init(t_expand *expand);

int	valid_quotes_env(t_expand *expand, char *str, int i);

#endif