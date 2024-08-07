#include "../../../include/minishell.h"

void	update_existing_node_else(t_env *tempo, t_data *data, char *str)
{
	char	*last_val;
	char	*tmp_val;

	last_val = NULL;
	tmp_val = get_value_env(str, data);
	if (tempo->value)
		last_val = ft_strdup(tempo->value, data);
	if (tempo->value)
	{
		free(tempo->value);
		tempo->value = ft_strjoin(last_val, tmp_val, data);
	}
	else
		tempo->value = ft_strdup(tmp_val, data);
	free(tmp_val);
	if (last_val)
		free(last_val);
}

void	update_existing_node(t_env *tempo, char *str, char *name, t_data *data)
{
	if (tempo->env_status == 0)
	{
		free(tempo->name);
		tempo->name = ft_strjoin(name, "=", data);
		tempo->value = get_value_env(str, data);
		tempo->env_status = 1;
	}
	else if (tempo->env_status == 1)
		update_existing_node_else(tempo, data, str);
}

int	cmd_export_plus_egal(t_data *data, char *str, char *val, char *new_name)
{
	t_env	*tempo;
	char	*tmp_name;
	char	*name;

	tempo = data->first_env;
	tmp_name = cmd_export_get_name(data, str);
	name = ft_substr(tmp_name, 0, ft_strlen(tmp_name) - 1, data);
	free(tmp_name);
	while (tempo)
	{
		if ((tempo->env_status == 0 || tempo->env_status == 1)
			&& ft_strncmp(name, tempo->name, ft_strlen(name)) == 0)
		{
			update_existing_node(tempo, str, name, data);
			return (free(name), 0);
		}
		tempo = tempo->next;
	}
	new_name = ft_strjoin(name, "=", data);
	val = ft_substr(str, (unsigned int)ft_strlen(new_name)
			+ 1, ft_strlen(str), data);
	new_node_env_w_data(val, new_name, 1, data);
	return (free(val), free(new_name), free(name), 0);
}

void	cmd_export_print(t_data *data, int fd)
{
	t_env	*temp;
	t_env	**env_array;
	int		count;
	int		i;

	i = 0;
	count = lst_env_size(data);
	env_array = (t_env **)malloc(count * sizeof(t_env *));
	if (!env_array)
		free_all(data, ERR_MAL, 0);
	temp = data->first_env;
	while (temp)
	{
		env_array[i++] = temp;
		temp = temp->next;
	}
	sort_tab(env_array, count);
	print_export(data, count, env_array, fd);
	free(env_array);
	g_exit_s = 0;
}
