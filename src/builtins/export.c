#include "../../include/minishell.h"

int	cmd_export_check_ascii(t_data *data)
{
	t_env *temp;
	int	check;
	// int	check2;

	temp = data->first_env;
	while (temp)
	{
		check = (int)temp->name[0];
		temp = temp->next;
	}
	return (0);
}



void	cmd_export_print(t_data *data, int fd)
{
	t_env	*temp;

	temp = data->first_env;
	while (temp)
	{
		if (temp->value)
			ft_printf_fd(fd, "declare -x %s\"%s\"\n", temp->name, temp->value);
		else if (temp->name[ft_strlen(temp->name) - 1] == '=')
			ft_printf_fd(fd, "declare -x %s\"\"\n", temp->name);
		else
			ft_printf_fd(fd, "declare -x %s\n", temp->name);
		temp = temp->next;
	}
	return ;
}

void	cmd_export(t_data *data, char **str, int fd)
{
	(void)data;
	(void)str;
	if (!str[1])
		cmd_export_print(data, fd);
	else
	{
		printf("EXPORT AUTRE CAS\n");
	}
}