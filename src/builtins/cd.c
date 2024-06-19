#include "../../include/minishell.h"

//avant de bouger, mettre le pwd actuel a la place du oldpwd dans env, ouis deplacer, et recup le pwd 
// et le mettre dans env

// ajt un char*str HOME DE BASE au cas ou (a recup avec getenv("HOME"))

// le ~ a gerer dans expand ????????

// void	cmd_cd_home_oldpwd(t_data *data, char *home, char *pwd_before)
// {
// 	t_env	*tempo;
// 	char	*str_tmp;

// 	tempo = data->first_env;
// 	if (!home)
// 		printf("????\n");
// 	while(tempo)
// 	{
// 		if (ft_strncmp("OLDPWD", tempo->name, 6) == 0)
// 		{
// 			printf("ui [%s]\n", tempo->name);
// 			free(tempo->value);
// 			tempo->value = ft_strdup(pwd_before, data);
// 			if (tempo->env_status == 0)
// 			{
// 				str_tmp = ft_strdup(tempo->name, data);
// 				free(tempo->name);
// 				tempo->name = ft_strjoin(str_tmp, "=", data);
// 			}
// 			tempo->env_status = 1;
// 			printf("C CHANGÉ\n");
// 			return ;
// 		}
// 		tempo = tempo->next;
// 	}
// }

// void	cmd_cd_home_change_pwd(t_data *data, char *home)
// {
// 	t_env	*tempo;
// 	char	*pwd_before;

// 	tempo = data->first_env;
// 	pwd_before = NULL;
// 	if (!home)
// 	{
// 		printf("MH PB\n");
// 		return ;
// 	}
// 	while(tempo)
// 	{
// 		if (ft_strncmp("PWD", tempo->name, 3) == 0)
// 		{
// 	printf("ui [%s]\n", tempo->name);
// 			pwd_before = ft_strdup(tempo->value, data);
// 			free(tempo->value);
// 			printf("ICI\n");
// 			tempo->value = ft_strdup(home, data);
// 			printf("C CHANGÉ\n");
// 			cmd_cd_home_oldpwd(data, home, pwd_before);
// 			return ;
// 		}
// 		tempo = tempo->next;
// 	}
// 	printf("nn\n");
// }

// char	*cmd_cd_home_get_home(t_data *data)
// {
// 	t_env *tempo;

// 	tempo = data->first_env;
// 	while (tempo)
// 	{
// 		if (ft_strncmp("HOME", tempo->name, 4) && ft_strlen(tempo->name) == 4)
// 			return (ft_strdup(tempo->value, data));
// 		tempo = tempo->next;
// 	}
// 	return (NULL);
// }

// void	cmd_cd_home(t_data *data)
// {
// //chercher le HOME DANS ENV;
// 	char	*home_path;
// 	int		check_chdir;

// 	home_path = cmd_cd_home_get_home(data);
// 	// (void)data;
// 	// home_path = "tessst";
// 	if (!home_path)
// 	{
// 		printf("cd: HOME not set\n");
// 		return ;
// 	}
// 	check_chdir = chdir(home_path);
// 	printf("ret chdir = %d | new pwd = %s\n", check_chdir, getenv("HOME"));
// 	if (check_chdir == -1)
// 	{
// 		// printf("cd: %s: No such file or directory\n", home_path);
// 		printf("BEN NON, ALLER AU HOME")
// 		free(home_path);
// 		return ;
// 	}
// 	//changer le pwd et le oldpwd dans env;
// 	cmd_cd_home_change_pwd(data, getenv("HOME"));
// 	free(home_path);
// 	return ;
// }

void	cmd_cd_change_pwd(t_data *data, char *new_pwd)
{
	t_env *tempo;

	tempo = data->first_env;
	while (tempo)
	{
		if (ft_strncmp("PWD=", tempo->name, 4) == 0 && ft_strlen(tempo->name) == 4)
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
		if (ft_strncmp("PWD=", tempo->name, 4) == 0 && ft_strlen(tempo->name) == 4)
		{
			new_oldpwd = ft_strdup(tempo->value, data);
			break;
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
	printf("AP %s\n", new_oldpwd);
	tempo = data->first_env;
	while (tempo)
	{
		if (ft_strncmp("OLDPWD", tempo->name, 6) == 0 && ((ft_strlen(tempo->name) == 6) || (ft_strlen(tempo->name) == 7)))
		{
			free(tempo->value);

			tempo->value = ft_strdup(new_oldpwd, data);
			printf("KCAV\n");
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
	printf("IHI\n");
	return ;
}


char	*cmd_cd_home_get_home(t_data *data)
{
	t_env *tempo;

	tempo = data->first_env;
	while (tempo)
	{
		if (ft_strncmp("HOME=", tempo->name, 5) == 0 && ft_strlen(tempo->name) == 5)
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

int	cmd_cd_path_file_or_dir_err(t_data *data, char *str)
{
	struct stat statbuf;

(void)data;
printf("AV STAT\n");
	if (stat(str, &statbuf) == 0)
	{
		printf("IN STAT\n");
		if (S_ISREG(statbuf.st_mode))
		{
			printf("cd: %s: Not a directory\n", str);
			return (-1);
		}

	}
	else
	{
		printf("cd: %s: No such file or directory\n", str);
		return (-1);
	}
	return 0;
}

void	cmd_cd_path(t_data *data, char *str)
{
	printf("ICI\n");
	if (cmd_cd_path_file_or_dir_err(data, str) == -1)
	{
		if (ft_strlen(str) == 2 && ft_strncmp("..", str, 2) == 0)
			cmd_cd_home(data);
		return ;
	}
	printf("ICI2\n");
	cmd_cd_home_change_oldpwd(data);
	printf("AVVCHDIR\n");
	chdir(str);
	printf("APCHDIR\n");
	cmd_cd_change_pwd(data, getcwd(NULL, 0));
	printf("APICI\n");
	return ;
}

void	cmd_cd(t_data *data, char **str, int fd)
{
	int	len_str2;
	(void)fd;
	(void)data;

	len_str2 = ft_strlen(str[1]);
	if (!str[1])
	{
		printf("CD : NO ARG\n");
		cmd_cd_home(data);
	}
	else if (len_str2 == 1 && ft_strncmp("-", str[1], 1) == 0)
		printf("RETOUR AU OLDPWD\n");
	else if (len_str2 == 2 && ft_strncmp("--", str[1], 2) == 0)
	{
		printf("CD : NO ARG\n");
		cmd_cd_home(data);
	}
	else if (len_str2 == 1 && ft_strncmp(".", str[1], 1) == 0)
		cmd_cd_home_change_oldpwd(data);
	else
	{
		printf("CHECK LE PATH ET Y ALLER\n");
		cmd_cd_path(data, str[1]);
	}
	return ;
}
