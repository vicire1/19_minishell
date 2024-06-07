#include "../../include/minishell.h"

void	free_two(void *first, void *sec)
{
	free(first);
	first = NULL;
	free(sec);
	sec = NULL;
	return ;
}
