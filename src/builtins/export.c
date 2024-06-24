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
	t_env *tempo;
	int		i;

	tempo = data->first_env;
	i = 0;
	while (i < count)
	{
		tempo = env_array[i];
		if (tempo->value)
			ft_printf_fd(fd, "declare -x %s\"%s\"\n",
				tempo->name, tempo->value);
		else if (tempo->name[ft_strlen(tempo->name) - 1] == '=')
			ft_printf_fd(fd, "declare -x %s\"\"\n", tempo->name);
		else
			ft_printf_fd(fd, "declare -x %s\n", tempo->name);
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
	printf("OK\n");
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
	if (!ft_isalnum(str[0]) && str[0] != '_')
		return (1);
	while (str[i] && str[i] != '=')
		i++;
	while (j < i)
	{
		if (!ft_isalnum(str[j]))
		{
			if (str[j] != '_')
				return (1);
		}
		j++;
	}
	return (0);
}

void	cmd_export_for_env(t_data *data, char **str)
{
	int	i;

(void)data;
	i = 1;
	while (str[i])
	{
		if (cmd_export_check_invalid(str[i]))
			printf("export : \'%s\': not a valid identifier\n", str[i]);
		/*
		else
			cmd_export_do_it(data, str[i]) // dedans, dabord suppri la node si il faut, puis add une node avec les bonnes infos
		*/
		printf("[%s]\n", str[i]);
		i++;
	}
}


void	cmd_export(t_data *data, char **str, int fd)
{
	(void)data;
	(void)str;
	if (!str[1])
		cmd_export_print(data, fd);
	else
	{
		printf("EXPORT AUTRE CAS\n");
		cmd_export_for_env(data, str);
	}
}
