#include "../../include/minishell.h"

void	cmd_cd_change_pwd(t_data *data, char *new_pwd)
{
	t_env	*tempo;
	char	*tmp;

	tempo = data->first_env;
	if (!new_pwd)
		return ;
	while (tempo)
	{
		if (ft_strncmp("PWD=", tempo->name, 4) == 0
			&& ft_strlen(tempo->name) == 4)
		{
			free(tempo->value);
			tempo->value = ft_strdup(new_pwd, data);
			free(new_pwd);
			return ;
		}
		tempo = tempo->next;
	}
	tmp = ft_strjoin("PWD=", new_pwd, data);
	new_node_env(tmp, 1, data);
	free(tmp);
	free(new_pwd);
}

char	*cmd_cd_home_get_new_oldpwd(t_data *data)
{
	t_env	*tempo;
	char	*new_oldpwd;

	tempo = data->first_env;
	new_oldpwd = NULL;
	while (tempo)
	{
		if (ft_strncmp("PWD=", tempo->name, 4) == 0
			&& ft_strlen(tempo->name) == 4)
		{
			new_oldpwd = ft_strdup(tempo->value, data);
			break ;
		}
		tempo = tempo->next;
	}
	if (!new_oldpwd)
		new_oldpwd = getcwd(NULL, 0);
	return (new_oldpwd);
}

int	cmd_cd_change_oldpwd(t_data *data, char *new_old, char *str_tmp, char *tmp)
{
	t_env	*tempo;

	tempo = data->first_env;
	while (tempo)
	{
		if (ft_strncmp("OLDPWD", tempo->name, 6) == 0
			&& ((ft_strlen(tempo->name) == 6) || (ft_strlen(tempo->name) == 7)))
		{
			free(tempo->value);
			tempo->value = ft_strdup(new_old, data);
			if (tempo->env_status == 0)
			{
				str_tmp = ft_strdup(tempo->name, data);
				free(tempo->name);
				tempo->name = ft_strjoin(str_tmp, "=", data);
				free(str_tmp);
				tempo->env_status = 1;
			}
			return (0);
		}
		tempo = tempo->next;
	}
	tmp = ft_strjoin("OLDPWD=", new_old, data);
	new_node_env(tmp, 1, data);
	return (free(tmp), 0);
}

/**
 * @brief check if the dir is correct
 * 
 * @param data struct data
 * @param str absolute path
 * @return int return 1 if incorrect or 0 if it is
 */
int	cmd_cd_path_file_or_dir_err( char *str)
{
	if (access(str, F_OK) == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s:  No such file or directory\n", str);
		exit_s = 1;
		return (1);
	}
	if (access(str, X_OK) == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: Permission denied\n", str);
		exit_s = 1;
		return (1);
	}
	return (0);
}
