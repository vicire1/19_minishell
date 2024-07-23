#include "../../include/minishell.h"

void	init_oldpwd(t_data *data)
{
	t_env	*temp;

	temp = data->first_env;
	while (temp)
	{
		if (ft_strncmp("OLDPWD", temp->name, 6) == 0)
			return ;
		temp = temp->next;
	}
	new_node_env("OLDPWD", 0, data);
}

void	init_pwd(t_data *data)
{
	t_env	*temp;
	char	*pwd;
	char	*tmp;

	temp = data->first_env;
	while (temp)
	{
		if (ft_strncmp("PWD", temp->name, 3) == 0)
			return ;
		temp = temp->next;
	}
	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", pwd, data);
	new_node_env(tmp, 1, data);
	free(tmp);
}

void	init_shlvl(t_data *data)
{
	t_env	*temp;
	int		shlvl;

	temp = data->first_env;
	while (temp)
	{
		if (ft_strncmp("SHLVL", temp->name, 5) == 0)
		{
			shlvl = atoi(temp->value);
			shlvl++;
			free(temp->value);
			temp->value = ft_itoa(shlvl, data);
			return ;
		}
		temp = temp->next;
	}
	new_node_env("SHLVL=1", 1, data);
}

void	init_export(t_data *data)
{
	init_oldpwd(data);
	init_pwd(data);
	init_shlvl(data);
}