#include "../../include/minishell.h"

char	*cmd_env(t_data *data)
{
	t_env *tempo;
	char *ret;
	char *tmp;

	tempo = data->first_env;

	printf("VIEMT\n");
	tmp = ft_strdup(tempo->env_str, data);
	tempo= tempo->next;
	while (tempo)
	{
		ret = ft_strjoin(tmp, tempo->env_str, data);
		free(tmp);
		tmp = ft_strdup(tempo->env_str, data);
		// ret = ft_strjoin(ret, "\n", data);

		tempo = tempo->next;
	}
	printf("%s\n", ret);
	return (ret);
}