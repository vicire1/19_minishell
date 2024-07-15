#include "../../include/minishell.h"

void	sort_tab(t_env **arr, int n)
{
	t_env	*key;
	int		j;
	int		i;

	i = 1;
	while (i < n)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && strcmp(arr[j]->name, key->name) > 0)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
		i++;
	}
}

int	lst_env_size(t_data *data)
{
	t_env	*tempo;
	int		ret;

	tempo = data->first_env;
	ret = 0;
	while (tempo)
	{
		ret++;
		tempo = tempo->next;
	}
	return (ret);
}

void	print_export(t_data *data, int count, t_env **env_array, int fd)
{
	t_env	*tempo;
	int		i;

	tempo = data->first_env;
	i = 0;
	while (i < count)
	{
		tempo = env_array[i];
		if (tempo->env_status == 0)
			ft_printf_fd(fd, "declare -x %s\n", tempo->name);
		if (tempo->value && tempo->env_status == 1)
			ft_printf_fd(fd, "declare -x %s\"%s\"\n",
				tempo->name, tempo->value);
		else if (tempo->name[ft_strlen(tempo->name) - 1] == '=')
			ft_printf_fd(fd, "declare -x %s\"\"\n", tempo->name);
		i++;
	}
	return ;
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
}

int	cmd_export_check_invalid(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_isdigit(str[0]))
		return (1);
	if (!ft_isalnum(str[0]) && str[0] != '_')
		return (1);
	while (str[i] && str[i] != '=')
		i++;
	while (j < i)
	{
		if (!ft_isalnum(str[j]))
		{
			if (str[j] != '_')
			{
				if (str[j] == '+' && str[j + 1] == '=')
					return (0);
				return (1);
			}
		}
		j++;
	}
	return (0);
}

int	cmd_export_check_plus_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i - 1] == '+')
		return (1);
	return (0);
}

int	cmd_export_check_egal_no_val(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i + 1 == (int)ft_strlen(str))
		return (1);
	return (0);
}

int	cmd_export_check_no_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	cmd_export_egal_no_val(t_data *data, char *str)
{
	t_env	*tempo;

	tempo = data->first_env;
	while (tempo)
	{
		if (ft_strncmp(str, tempo->name, ft_strlen(tempo->name)) == 0)
		{
			tempo->env_status = 1;
			free(tempo->name);
			tempo->name = ft_strdup(str, data);
			if (tempo->value)
				free(tempo->value);
			tempo->value = NULL;
			return ;
		}
		tempo = tempo->next;
	}
	new_node_env_w_data(NULL, str, 1, data);
}

void	cmd_export_no_egal(t_data *data, char *str)
{
	t_env	*tempo;

	tempo = data->first_env;
	while (tempo)
	{
		if (ft_strncmp(str, tempo->name, ft_strlen(str)) == 0)
			return ;
		tempo = tempo->next;
	}
	new_node_env(str, 0, data);
}

char	*cmd_export_get_name(t_data *data, char *str)
{
	int	size;

	size = 0;
	while (str[size] != '=' && str[size])
		size++;
	return (ft_substr(str, 0, size, data));
}

void	cmd_export_egal_val(t_data *data, char *str)
{
	t_env	*tempo;
	char	*name;

	name = cmd_export_get_name(data, str);
	tempo = data->first_env;
	while (tempo)
	{
		if (tempo->env_status == 0
			&& (ft_strncmp(name, tempo->name, ft_strlen(name)) == 0))
		{
			cmd_unset_do_it_sec(data, name);
			break ;
		}
		else if (tempo->env_status == 1
			&& (ft_strncmp(name, tempo->name, ft_strlen(name)) == 0))
		{
			cmd_unset_do_it(data, name);
			break ;
		}
		tempo = tempo->next;
	}
	free(name);
	new_node_env(str, 1, data);
}

void	cmd_export_plus_egal(t_data *data, char *str)
{
	t_env	*tempo;
	char	*tmp_name;
	char	*tmp_val;
	char	*last_val;
	char	*name;
	char	*new_name;
	char	*val;

	tmp_name = cmd_export_get_name(data, str);
	last_val = NULL;
	name = ft_substr(tmp_name, 0, ft_strlen(tmp_name) -1, data);
	free(tmp_name);
	tempo = data->first_env;
	while (tempo)
	{
		if (tempo->env_status == 0
			&& (ft_strncmp(name, tempo->name, ft_strlen(name)) == 0))
		{
			free(tempo->name);
			tempo->name = ft_strjoin(name, "=", data);
			free(name);
			free(tmp_name);
			tempo->value = get_value_env(str, data);
			tempo->env_status = 1;
			return ;
		}
		else if (tempo->env_status == 1
			&& (ft_strncmp(name, tempo->name, ft_strlen(name)) == 0))
		{
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
			free(last_val);
			return ;
		}
		tempo = tempo->next;
	}
	new_name = ft_strjoin(name, "=", data);
	val = ft_substr(str, (unsigned int)ft_strlen(new_name) + 1, ft_strlen(str), data);
	new_node_env_w_data(val, new_name, 1, data);
	free(val);
	free(new_name);
	return ;
}

void	cmd_export_for_env(t_data *data, char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (cmd_export_check_invalid(str[i]))
			ft_printf_fd(2, "minishell: export : `%s\': not a valid identifier\n", str[i]);
		else if (cmd_export_check_plus_egal(str[i]))
			cmd_export_plus_egal(data, str[i]);
		else if (cmd_export_check_egal_no_val(str[i]))
		{
			cmd_export_egal_no_val(data, str[i]);
		}
		else if (cmd_export_check_no_egal(str[i]))
			cmd_export_no_egal(data, str[i]);
		else
			cmd_export_egal_val(data, str[i]);
		i++;
	}
}

void	cmd_export(t_data *data, char **str)
{
	if (!str[1])
		cmd_export_print(data, 1);
	else
		cmd_export_for_env(data, str);
}
