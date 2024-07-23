#include "../../include/minishell.h"

char	*get_name_env(char *str, t_data *data)
{
	int	size;

	size = 0;
	while (str[size] && str[size] != '=')
		size++;
	if ((int)ft_strlen(str) > size)
		size++;
	return (ft_substr(str, 0, size, data));
}

char	*get_value_env(char *str, t_data *data)
{
	int	size;

	size = 0;
	while (str[size] && str[size] != '=')
		size++;
	if (!str[size])
		return (NULL);
	if ((str[size] != '=' && str[size + 1])
		|| (str[size] == '=' && !str[size + 1]))
		return (NULL);
	return (ft_substr(str, size + 1, ft_strlen(str), data));
}

int	new_node_env(char *str, int status, t_data *data)
{
	t_env	*new;
	t_env	*temp;

	new = malloc(sizeof(t_env));
	if (!new)
		free_all(data, ERR_MAL, 1);
	new->next = NULL;
	new->env_status = status;
	new->name = get_name_env(str, data);
	new->value = get_value_env(str, data);
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

int	new_node_env_w_data(char *val, char *name, int status, t_data *data)
{
	t_env	*new;
	t_env	*temp;

	new = malloc(sizeof(t_env));
	if (!new)
		free_all(data, ERR_MAL, 1);
	new->next = NULL;
	new->env_status = status;
	new->name = ft_strdup(name, data);
	new->value = NULL;
	if (val)
		new->value = ft_strdup(val, data);
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
