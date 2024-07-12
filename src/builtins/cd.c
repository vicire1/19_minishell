#include "../../include/minishell.h"

void	cmd_cd_change_pwd(t_data *data, char *new_pwd)
{
	t_env	*tempo;

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
		printf("cd: HOME not set\n");
		return ;
	}
	if (access(home_path, F_OK) == -1)
	{
		printf("cd: %s: No such file or directory\n", home_path);
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
int	cmd_cd_path_file_or_dir_err(t_data *data, char *str)
{
	(void)data;
	printf("%s\n", str);
	if (access(str, F_OK) == -1)
	{
		printf("cd: %s:  No such file or directory\n", str);
		return (1);
	}
	if (access(str, X_OK) == -1)
	{
		printf("cd: %s: Permission denied\n", str);
		return (1);
	}
	return (0);
}
/*
a cause de chmod 000
midif la fctn au dessus, utiliser avec access, pour F_OK (si mauvais No such file or dir), puis X_OK (si mauvais Permission denied)
*/





/**
 * @brief Hendle the 'cd' command with path
 * 
 * @param data struct data
 * @param str arg
 */
void	cmd_cd_path(t_data *data, char *str)
{
	if (cmd_cd_path_file_or_dir_err(data, str))
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

/**
 * @brief Handles the 'cd' command to change the current directory.
 * 
 * @param data struct data
 * @param str [0] => cd [.;.;.]=> arg
 * @param fd file descriptor (unused)
 */
void	cmd_cd(t_data *data, char **str, int fd)
{
	int	len_str2;

	(void)fd;
	len_str2 = ft_strlen(str[1]);
	if (!str[1])
		cmd_cd_home(data);
	else if (len_str2 == 1 && ft_strncmp("-", str[1], 1) == 0)
		printf("RETOUR AU OLDPWD\n");
	else if (len_str2 == 2 && ft_strncmp("--", str[1], 2) == 0)
		cmd_cd_home(data);
	else if (len_str2 == 1 && ft_strncmp(".", str[1], 1) == 0)
		cmd_cd_home_change_oldpwd(data);
	else
		cmd_cd_path(data, str[1]);
	return ;
}

/*
	a faire :	si le PWD est unset, en refaire un nouveau !
				si le OLDPWD est unset, en refaire un nouveau (att pas la premiere fois mais la 2eme idk ?) ! 
*/