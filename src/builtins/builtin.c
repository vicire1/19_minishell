#include "../../include/minishell.h"

/**
 * @brief check if str is a builtin
 * 
 * @param str string to compare
 * @return int which builtin is it or if it s not
 */
int	check_if_builtin(char *str)
{
	int	len_str;

	len_str = ft_strlen(str);
	if (len_str == 3 && ft_strncmp("pwd", str, 3) == 0)
		return (1);
	else if (len_str == 3 && ft_strncmp("env", str, 3) == 0)
		return (2);
	else if (len_str == 6 && ft_strncmp("export", str, 6) == 0)
		return (3);
	else if (len_str == 2 && ft_strncmp("cd", str, 2) == 0)
		return (4);
	else if (len_str == 5 && ft_strncmp("unset", str, 5) == 0)
		return (5);
	else if (len_str == 4 && ft_strncmp("echo", str, 4) == 0)
		return (6);
	else if (len_str == 4 && ft_strncmp("exit", str, 4) == 0)
		return (7);
	return (0);
}

/**
 * @brief dispatch builtins
 * 
 * @param data struct data
 * @param str char** 
 * @param fd file descriptor
 * @param which which builtin is it
 */
void	dispatch_builtins(t_data *data, char **str, int fd, int which)
{
	(void)str;
	if (which == 1)
		cmd_pwd(data, fd);
	else if (which == 2)
		cmd_env(data, str, fd);
	else if (which == 3)
		cmd_export(data, str, fd);
	else if (which == 4)
		cmd_cd(data, str, fd);
	else if (which == 5)
		cmd_unset(data, str, fd);
	else if (which == 6)
		cmd_echo(data, str, fd);
	else if (which == 7)
		cmd_exit(data, str);
	return ;
}
