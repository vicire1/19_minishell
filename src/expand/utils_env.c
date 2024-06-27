#include "../../include/minishell.h"

void	print_env(t_data *data)
{
	t_env	*temp;

	temp = data->first_env;
	printf("----------------------\n");
	while (temp)
	{
		printf("string : %s%s\n", temp->name, temp->value);
		// printf("\033[1;31madr : %p | prev adr : %p | next adr : %p\n\033[0m", temp, temp->prev, temp->next);
		temp = temp->next;
	}
	printf("----------------------\n");
}

void	init_export(t_data *data)
{
	t_env	*temp;

	temp = data->first_env;
	while(temp)
	{
		if (ft_strncmp("OLDPWD", temp->name, 6) == 0)
		{
			return ;
		}
		temp = temp->next;
	}
	new_node_env("OLDPWD", 0, data);

}

char	*get_name_env(char *str, t_data *data)
{
	int	size;

	size = 0;
	while (str[size] && str[size] != '=')
		size++;
	if (str[size + 1])
		size++;
	if (str[size] == '=')
		size++;
	return (ft_substr(str, 0, size, data));
}

char *get_value_env(char *str, t_data *data)
{
	int size;

	size = 0;
	while (str[size] && str[size] != '=')
		size++;
	if ((str[size] != '=' && str[size + 1]) || (str[size] == '=' && !str[size + 1]))
		return (NULL);
	return(ft_substr(str, size + 1, ft_strlen(str), data));
}

int	new_node_env(char *str, int status, t_data *data)
{
	t_env		*new;
	t_env		*temp;

	new = malloc(sizeof(t_env));
	if (!new)
		free_all(data, ERR_MAL, 1);
	new->next = NULL;
	new->env_status = status;
	new->name = get_name_env(str, data);
	new->value = get_value_env(str, data);
	// printf("NAME | VALUE = [%s][%s]\n", new->name, new->value);
	if (data->first_env == NULL)
	{
		new->prev = NULL;
		data->first_env = new;
		return (0);
	}
	temp = data->first_env;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	return (0);
}
