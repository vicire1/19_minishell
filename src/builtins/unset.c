#include "../../include/minishell.h"

// ! suppr tout

int		cmd_unset_check_invalid(char *str)
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

int		cmd_unset_check_in_env(t_data *data, char *str)
{
	t_env	*tempo;
	int		size_str;
	int		size_name;

	tempo = data->first_env;
	size_str = ft_strlen(str);
	while(tempo)
	{
		size_name = ft_strlen(tempo->name);
		if (((size_name - 1) == size_str) && ft_strncmp(tempo->name, str, size_str) == 0)
			return (1);
		tempo = tempo->next;
	}
	return (0);
}

void cmd_unset_do_it(t_data *data, char *str)
{
	t_env	*tempo;
	int		size_str;
	int		size_name;

	tempo = data->first_env;
	size_str = ft_strlen(str);
	while (tempo)
	{
		size_name = ft_strlen(tempo->name);
		if (((size_name - 1) == size_str)
			&& ft_strncmp(tempo->name, str, size_str) == 0)
		{
			if (tempo->prev == NULL) 
			{
				data->first_env = (t_env *)tempo->next;
				if (tempo->next != NULL) 
					((t_env *)tempo->next)->prev = NULL;
			}
			else
			{
				((t_env *)tempo->prev)->next = tempo->next;
				if (tempo->next != NULL)
					((t_env *)tempo->next)->prev = tempo->prev;
			}
			free(tempo->name);
			free(tempo->value);
			free(tempo);
			return ;
		}
		tempo = (t_env *)tempo->next;
	}
}


void	cmd_unset(t_data *data, char **str, int fd)
{
	int	i;
	(void)fd;
	if (!str[1])
		return ;
	i = 1;
	while (str[i])
	{
		if (cmd_unset_check_in_env(data, str[i]))
		{
			printf("FAUT UNSET ->%s\n", str[i]);
			cmd_unset_do_it(data, str[i]);
		}
		else if (cmd_unset_check_invalid(str[i]))
			printf("unset : \'%s\': not a valid identifier\n", str[i]);
		else
			printf("FAUT PAS UNSET ->%s\n", str[i]);
		i++;
	}
	return ;
}