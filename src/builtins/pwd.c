#include "../../include/minishell.h"

//return quoi ? char *?

//utiliser getcwd
char	*cmd_pwd(t_data *data)
{
	(void)data;
	char *test;

	test = getcwd(NULL, 0);
	printf("%s\n", test);
	free(test);
	return (NULL);
}