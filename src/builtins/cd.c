#include "../../include/minishell.h"

void	cmd_cd_change_pwd(t_data *data, char *new_pwd)
{
	t_env	*tempo;
	char	*tmp;

	tempo = data->first_env;
	if (!new_pwd)
		free_all(data, ERR_GETCWD, 1);
	while (tempo)
	{
		if (ft_strncmp("PWD=", tempo->name, 4) == 0
			&& ft_strlen(tempo->name) == 4)
		{
			free(tempo->value);
			tempo->value = ft_strdup(new_pwd, data);
			return ;
		}
		tempo = tempo->next;
	}
	tmp = ft_strjoin("PWD=", new_pwd, data);
	new_node_env(tmp, 1, data);
	free(tmp);
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

void	cmd_cd_home_change_oldpwd(t_data *data)
{
	t_env	*tempo;
	char	*new_oldpwd;
	char	*str_tempo;

	new_oldpwd = cmd_cd_home_get_new_oldpwd(data);
	tempo = data->first_env;
	while (tempo)
	{
		if (ft_strncmp("OLDPWD", tempo->name, 6) == 0
			&& ((ft_strlen(tempo->name) == 6) || (ft_strlen(tempo->name) == 7)))
		{
			free(tempo->value);
			tempo->value = ft_strdup(new_oldpwd, data);
			if (tempo->env_status == 0)
			{
				str_tempo = ft_strdup(tempo->name, data);
				free(tempo->name);
				tempo->name = ft_strjoin(str_tempo, "=", data);
				free(str_tempo);
				tempo->env_status = 1;
			}
			return ;
		}
		tempo = tempo->next;
	}
	return ;
}

char	*cmd_cd_home_get_home(t_data *data)
{
	t_env	*tempo;

	tempo = data->first_env;
	while (tempo)
	{
		if (ft_strncmp("HOME=", tempo->name, 5) == 0
			&& ft_strlen(tempo->name) == 5)
			return (ft_strdup(tempo->value, data));
		tempo = tempo->next;
	}
	return (NULL);
}

void	cmd_cd_home(t_data *data)
{
	char	*home_path;

	home_path = cmd_cd_home_get_home(data);
	if (!home_path)
	{
		ft_printf_fd(2, "minishell: cd: HOME not set\n");
		exit_s = 1;
		return ;
	}
	if (access(home_path, F_OK) == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", home_path);
		return ;
	}
	if (access(home_path, X_OK) == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: Permission denied\n", home_path);
		exit_s = 1;
		return ;
	}
	cmd_cd_home_change_oldpwd(data);
	chdir(home_path);
	cmd_cd_change_pwd(data, home_path);
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

/**
 * @brief Hendle the 'cd' command with path
 * 
 * @param data struct data
 * @param str arg
 */
void	cmd_cd_path(t_data *data, char *str)
{
	if (cmd_cd_path_file_or_dir_err(str))
	{
		if (ft_strlen(str) == 2 && ft_strncmp("..", str, 2) == 0)
			cmd_cd_home(data);
		return ;
	}
	cmd_cd_home_change_oldpwd(data);
	chdir(str);
	cmd_cd_change_pwd(data, getcwd(NULL, 0));
	return ;
}

void	cmd_cd_dash(t_data *data)
{
	char	*OLDPWD;
	t_env	*tmp;

	OLDPWD = NULL;
	tmp = data->first_env;
	while (tmp)
	{
		if (ft_strncmp("OLDPWD=", tmp->name, 7) == 0
			&& ft_strlen(tmp->name) == 7)
		{
			OLDPWD = ft_strdup(tmp->value, data);
			break ;
		}
		tmp = tmp->next;
	}
	if (!cmd_cd_path_file_or_dir_err(OLDPWD))
	{
		cmd_cd_home_change_oldpwd(data);
		chdir(OLDPWD);
		cmd_cd_change_pwd(data, getcwd(NULL, 0));
		free(OLDPWD);
		exit_s = 0;
	}
}

/**
 * @brief Handles the 'cd' command to change the current directory.
 * 
 * @param data struct data
 * @param str [0] => cd [.;.;.]=> arg
 */
void	cmd_cd(t_data *data, char **str)
{
	int	len_str2;

	len_str2 = ft_strlen(str[1]);
	if (!str[1])
		cmd_cd_home(data);
	else if (len_str2 == 1 && ft_strncmp("-", str[1], 1) == 0)
		cmd_cd_dash(data);
	else if (len_str2 == 2 && ft_strncmp("--", str[1], 2) == 0)
		cmd_cd_home(data);
	else if (len_str2 == 1 && ft_strncmp(".", str[1], 1) == 0)
		cmd_cd_home_change_oldpwd(data);
	else
		cmd_cd_path(data, str[1]);
	if (cmd_unset_check_in_env(data, "PWD"))
	{
		
		printf("PWD IN ENV    %s   \n", getcwd(NULL, 0));
		
	}
	else
		printf("PWD NOT IN ENV\n");
	return ;
}

/*
	a faire :	si le PWD est unset, en refaire un nouveau !
				si le OLDPWD est unset, en refaire un nouveau (att pas la premiere fois mais la 2eme idk ?) ! 
*/