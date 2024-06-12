#include "../../include/minishell.h"

char *check_if_builtin(t_data *data, char *str)
{
	int	len_str;

	len_str = ft_strlen(str);
	if (len_str == 3 && ft_strncmp("pwd", str,  3) == 0)
		return (cmd_pwd(data));
	else if (len_str == 3 && ft_strncmp("env", str,  3) == 0)
		return (cmd_env(data));
	return (NULL);
}