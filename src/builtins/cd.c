#include "../../include/minishell.h"

//avant de bouger, mettre le pwd actuel a la place du oldpwd dans env, ouis deplacer, et recup le pwd 
// et le mettre dans env

// ajt un char*str HOME DE BASE au cas ou (a recup avec getenv("HOME"))

// le ~ a gerer dans expand ????????
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

	home_path = cmd_cd_home_get_home(data);
	int		check_chdir;
	if (!home_path)
	{
		printf("cd: HOME not set\n");
		return ;
	}
	check_chdir = chdir(home_path);
	printf("new pwd = %s\n", getenv("HOME"));
	if (check_chdir == -1) //erreur
	{
		//creer le home_path de la ou je suis
		//chdir vers le home path;
	}
	//changer le pwd et le oldpwd dans env;
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