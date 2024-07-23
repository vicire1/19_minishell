#include "../../include/minishell.h"

int	in_env_sec(t_data *data, t_expander *expa, char *str)
{
	char	*tempo;
	char	*tempo2;

	expa->exit_check = 0;
	if (str[0] == '?')
	{
		tempo = ft_itoa(exit_s, data);
		tempo2 = ft_strjoin("i", "=", data);
		expa->tmp_val = ft_strjoin(tempo2, tempo, data);
		free(tempo);
		free(tempo2);
		expa->exit_check = 1;
		return (1);
	}
	return (0);
}

int	in_env(t_data *data, t_env *env, char *str, t_expander *expa)
{
	int		i;
	char	*tempo;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	tempo = ft_substr(str, 0, i, data);
	while (env)
	{
		if (env_cmp(tempo, env->name))
		{
			free(tempo);
			expa->tmp_val = ft_strjoin(env->name, env->value, data);
			if (!expa->tmp_val)
				expa->tmp_val = ft_strdup(env->name, data);
			return (1);
		}
		env = env->next;
	}
	return (free(tempo), in_env_sec(data, expa, str));
}
