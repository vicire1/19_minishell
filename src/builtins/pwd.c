#include "../../include/minishell.h"

//return quoi ? char *?

//utiliser getcwd
void	cmd_pwd(t_data *data, int fd)
{
	(void)data;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_printf_fd(fd, "%s\n", pwd);
	free(pwd);
	return ;
}