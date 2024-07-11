#include "../../include/minishell.h"

int	cmd_env_check_arg(char *str)
{
	if (!str)
		return (0);
	if (str[1] == '-')
	{
		printf("No option allowed for env\n");
		exit_s = 1;	
		return (1);
	}
	printf("No argument allowed for env\n");
	exit_s = 1;
	return (1);
}

void	cmd_env(t_data *data, char **str, int fd)
{
	t_env	*tempo;

	tempo = data->first_env;
	if (cmd_env_check_arg(str[1]))
		return ;
	while (tempo)
	{
		if (tempo->env_status)
		{
			if (tempo->name && tempo->value)
				ft_printf_fd(fd, "%s%s\n", tempo->name, tempo->value);
			else
				ft_printf_fd(fd, "%s\n", tempo->name);
		}
		tempo = tempo->next;
	}
	exit_s = 0;
	return ;
}
