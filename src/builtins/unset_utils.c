#include "../../include/minishell.h"

int	cmd_unset_check_invalid(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
		{
			if (str[i] != '_')
				return (1);
		}
		i++;
	}
	return (0);
}

int	cmd_unset_check_in_env(t_data *data, char *str)
{
	t_env	*tempo;

	tempo = data->first_env;
	while (tempo)
	{
		if (tempo->env_status
			&& (ft_strncmp(str, tempo->name, ft_strlen(str)) == 0))
			return (1);
		tempo = tempo->next;
	}
	return (0);
}
