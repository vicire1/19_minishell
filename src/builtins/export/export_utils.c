#include "../../../include/minishell.h"

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

char	*cmd_export_get_name(t_data *data, char *str)
{
	int	size;

	size = 0;
	while (str[size] != '=' && str[size])
		size++;
	return (ft_substr(str, 0, size, data));
}
