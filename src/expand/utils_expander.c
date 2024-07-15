#include "../../include/minishell.h"

int	size_env_doll(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	return (i);
}

int	size_env_name(char *env_line)
{
	int	i;

	i = 0;
	while (env_line[i] != '=')
		i++;
	return (i + 1);
}

int	size_env_value(char *env_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!env_line)
		return (0);
	while (env_line[i] && env_line[i] != '=')
	{
		i++;
	}
	while (env_line[i])
	{
		j++;
		i++;
	}
	return (j - 1);
}

int	env_cmp(char *str, char *str_env)
{
	int	i;

	i = 0;
		// printf("CMP [%s] et [%s]\n", str, str_env);
	while (str[i] && str_env[i])
	{
		if (str[i] != str_env[i])
			return (0);
		i++;
	}
	if (str_env[i] != '=')
		return (0);
	return (1);
}

int	check_v_env(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			j++;
		i++;
	}
	return (j);
}
