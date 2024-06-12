#include "../../include/minishell.h"

void	cmd_env(t_data *data, int fd)
{
	t_env *tempo;

	tempo = data->first_env;


	while (tempo)
	{
		if (tempo->env_status)
			ft_printf_fd(fd, "%s\n", tempo->env_str);
		tempo = tempo->next;
	}
	return ;
}