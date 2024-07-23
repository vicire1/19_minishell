#include "../../../include/minishell.h"

int	cmd_export_check_plus_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i - 1] == '+')
		return (1);
	return (0);
}

int	cmd_export_check_egal_no_val(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i + 1 == (int)ft_strlen(str))
		return (1);
	return (0);
}

int	cmd_export_check_no_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}
