#include "../../include/minishell.h"

//avant de bouger, mettre le pwd actuel a la place du oldpwd dans env, ouis deplacer, et recup le pwd 
// et le mettre dans env

// ajt un char*str HOME DE BASE au cas ou (a recup avec getenv("HOME"))

// le ~ a gerer dans expand ????????

void	cmd_cd_home_oldpwd(t_data *data, char *home, char *pwd_before)
{
	t_env	*tempo;
	char	*str_tmp;

	tempo = data->first_env;
	if (!home)
		printf("????\n");
	while(tempo)
	{
		if (ft_strncmp("OLDPWD", tempo->name, 6) == 0)
		{
			printf("ui [%s]\n", tempo->name);
			free(tempo->value);
			tempo->value = ft_strdup(pwd_before, data);
			if (tempo->env_status == 0)
			{
				str_tmp = ft_strdup(tempo->name, data);
				free(tempo->name);
				tempo->name = ft_strjoin(str_tmp, "=", data);
			}
			tempo->env_status = 1;
			printf("C CHANGÉ\n");
			return ;
		}
		tempo = tempo->next;
	}
}

void	cmd_cd_home_change_pwd(t_data *data, char *home)
{
	t_env	*tempo;
	char	*pwd_before;

	tempo = data->first_env;
	pwd_before = NULL;
	if (!home)
	{
		printf("MH PB\n");
		return ;
	}
	while(tempo)
	{
		if (ft_strncmp("PWD", tempo->name, 3) == 0)
		{
	printf("ui [%s]\n", tempo->name);
			pwd_before = ft_strdup(tempo->value, data);
			free(tempo->value);
			printf("ICI\n");
			tempo->value = ft_strdup(home, data);
			printf("C CHANGÉ\n");
			cmd_cd_home_oldpwd(data, home, pwd_before);
			return ;
		}
		tempo = tempo->next;
	}
	printf("nn\n");
}

char	*cmd_cd_home_get_home(t_data *data)
{
	t_env *tempo;

	tempo = data->first_env;
	while (tempo)
	{
		if (ft_strncmp("HOME", tempo->name, 4) && ft_strlen(tempo->name) == 4)
			return (ft_strdup(tempo->value, data));
		tempo = tempo->next;
	}
	return (NULL);
}

void	cmd_cd_home(t_data *data)
{
//chercher le HOME DANS ENV;
	char	*home_path;
	int		check_chdir;

	home_path = cmd_cd_home_get_home(data);
	// (void)data;
	// home_path = "tessst";
	if (!home_path)
	{
		printf("cd: HOME not set\n");
		return ;
	}
	check_chdir = chdir(home_path);
	printf("ret chdir = %d | new pwd = %s\n", check_chdir, getenv("HOME"));
	if (check_chdir == -1)
	{
		printf("cd: %s: No such file or directory\n", home_path);
		free(home_path);
		return ;
	}
	//changer le pwd et le oldpwd dans env;
	cmd_cd_home_change_pwd(data, getenv("HOME"));
	free(home_path);
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
		printf("BACK to HOME (si pas de HOME dans env \"cd: HOME not set\"\n");
		cmd_cd_home(data);
	}
	else if (len_str2 == 1 && ft_strncmp("-", str[1], 1) == 0)
		printf("RETOUR AU OLDPWD\n");
	else if (len_str2 == 2 && ft_strncmp("--", str[1], 2) == 0)
	{
		printf("BACK to HOME (si pas de HOME dans env \"cd: HOME not set\"\n");
		cmd_cd_home(data);
	}
	else
		printf("CHECK LE PATH ET Y ALLER\n");
	return ;
}