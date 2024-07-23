#include "../../include/minishell.h"

void	cmd_exit_do_it(t_data *data, long exitt)
{
	if (exitt < 0 || exitt > 255)
		exitt = exitt % 256;
	if (exitt < 0)
		exitt = exitt + 256;
	exit_s = (int)exitt;
	free_all(data, NULL, 1);

}

void	cmd_exit(t_data *data, char **str)
{
	if (!str[1])
		free_all(data, NULL, 1);
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
	cmd_exit_do_it(data, cmd_exit_convert(str[1]));
	return ;
}
