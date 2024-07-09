#include "../../include/minishell.h"


int	cmd_echo_check_n(char **str, int which)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str[which]);
	if (str[which][i] != '-' || len < 2)
		return (0);
	i++;
	while (str[which][i])
	{
		if (str[which][i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	cmd_echo_n_do_it(char **str, int fd)
{
	int	i;
	int	start;
	int	finish;

	i = 2;
	while (cmd_echo_check_n(str, i))
		i++;
	start = i;
	while (str[i])
		i++;
	finish = i - 1;
	while (start < finish)
	{
		ft_printf_fd(fd, "%s ", str[start]);
		start++;
	}
	ft_printf_fd(fd, "%s", str[start]);
	return ;
}

void	cmd_echo_do_it(char **str, int fd)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (str[i])
		i++;
	i-=1;
	while (j < i)
	{
		ft_printf_fd(fd, "%s ", str[j]);
		j++;
	}
	ft_printf_fd(fd, "%s\n", str[j]);
	return ;
}

void	cmd_echo(t_data *data, char **str, int fd)
{
	(void)data;
	if (!str[1])
	{
		ft_printf_fd(fd, "\n");
		exit_s = 0;
		return ;
	}
	else if (cmd_echo_check_n(str, 1))
	{
		cmd_echo_n_do_it(str, fd);
		exit_s = 0;
		return ;
	}
	else
		cmd_echo_do_it(str, fd);
	exit_s = 0;
	return ;
}