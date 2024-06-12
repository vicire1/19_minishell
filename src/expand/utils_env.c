#include "../../include/minishell.h"

void	print_env(t_data *data)
{
	t_env	*temp;

	temp = data->first_env;
	printf("----------------------\n");
	while (temp->next)
	{
		printf("string : %s\n", temp->env_str);
		printf("\033[1;31madr : %p | prev adr : %p | next adr : %p\n\033[0m", temp, temp->prev, temp->next);
		temp = temp->next;
	}
	printf("string : %s\n", temp->env_str);
	printf("\033[1;31madr : %p | prev adr : %p | next adr : %p\n\033[0m", temp, temp->prev, temp->next);
	printf("----------------------\n");
}

int	new_node_env(char *str, t_data *data)
{
	t_env		*new;
	t_env		*temp;

	new = malloc(sizeof(t_env));
	if (!new)
		free_all(data, ERR_MAL, 1);
	new->next = NULL;
	new->env_str = ft_strdup(str, data);
	if (data->first_env == NULL)
	{
		new->prev = NULL;
		data->first_env = new;
		return (0);
	}
	temp = data->first_env;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	return (0);
}
