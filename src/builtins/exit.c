#include "../../include/minishell.h"

void	cmd_exit_do_it(long exit)
{
	if (exit < 0 || exit > 255)
		exit = exit % 256;
	if (exit < 0)
		exit = exit + 256;
	exit_s = (int)exit;
}

void	cmd_exit(t_data *data, char **str)
{
	(void)data;
	if (!str[1])
	{
		exit(0);
	}
	else if (str[1])
	{
		if (cmd_exit_check_num(str[1]))
		{
			ft_printf_fd(2, "exit: %s: numeric argument required\n", str[1]);
			exit_s = 255;
			return ;
		}
	}
	if (str[2])
	{
		ft_printf_fd(2, "exit: too many arguments\n");
		exit_s = 1;
		return ;
	}
	cmd_exit_do_it(cmd_exit_convert(str[1]));
	return ;
}
