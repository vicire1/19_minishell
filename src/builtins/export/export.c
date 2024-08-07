#include "../../../include/minishell.h"

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
			cmd_unset_do_it_sec(data, name, 0);
			break ;
		}
		else if (tempo->env_status == 1
			&& (ft_strncmp(name, tempo->name, ft_strlen(name)) == 0))
		{
			cmd_unset_do_it(data, name, 0, 0);
			break ;
		}
		tempo = tempo->next;
	}
	free(name);
	new_node_env(str, 1, data);
}

void	cmd_export_for_env(t_data *data, char **str, int i)
{
	while (str[i])
	{
		if (cmd_export_check_invalid(str[i]))
		{
			ft_printf_fd(2,
				"minishell: export : `%s\': not a valid identifier\n", str[i]);
			g_exit_s = 1;
		}
		else if (cmd_export_check_plus_egal(str[i]))
			cmd_export_plus_egal(data, str[i], NULL, NULL);
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
		cmd_export_for_env(data, str, 1);
}
