#include "../../include/minishell.h"

/**
 * @brief check if there is an option or an arg
 * 
 * @param str str to check
 * @return int 0 if there isn't or 1 if there is
 */
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

/**
 * @brief handle the "env" command
 * 
 * @param data struct data
 * @param str cmd, option or arg
 * @param fd file descriptor
 */
void	cmd_env(t_data *data, char **str)
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
				ft_printf_fd(1, "%s%s\n", tempo->name, tempo->value);
			else
				ft_printf_fd(1, "%s\n", tempo->name);
		}
		tempo = tempo->next;
	}
	exit_s = 0;
	return ;
}
