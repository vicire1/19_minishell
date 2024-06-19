#include "../../include/minishell.h"

void	cmd_env(t_data *data, char **str, int fd)
{
	t_env *tempo;

	tempo = data->first_env;

	if (str[1])
	{
		printf("No option allowed for env\n");
		return ;
	}
	while (tempo)
	{
		if (tempo->env_status)
			ft_printf_fd(fd, "%s%s\n", tempo->name, tempo->value);
		tempo = tempo->next;
	}
	return ;
}
