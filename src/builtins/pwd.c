#include "../../include/minishell.h"

/**
 * @brief handle the "pwd" command
 * 
 * @param data struct data (unused)
 * @param fd file descritpor
 */
void	cmd_pwd(t_data *data)
{
	char	*pwd;
	t_env	*tempo;

	tempo = data->first_env;
	pwd = getcwd(NULL, 0);
	if (pwd)
		ft_printf_fd(1, "%s\n", pwd);
	else
	{
		while (tempo)
		{
			if (ft_strncmp(tempo->name, "PWD=", 4) == 0)
			{
				ft_printf_fd(1, "%s\n", tempo->value);
				break ;
			}
			tempo = tempo->next;
		}
	}
	if (pwd)
		free(pwd);
	g_exit_s = 0;
	return ;
}
