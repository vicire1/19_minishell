/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:09:32 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/08 14:13:52 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_if_builtin(char *str)
{
	int	len_str;

	len_str = ft_strlen(str);
	if (len_str == 3 && ft_strncmp("pwd\0", str, 4) == 0)
		return (1);
	else if (len_str == 3 && ft_strncmp("env\0", str, 4) == 0)
		return (2);
	else if (len_str == 6 && ft_strncmp("export\0", str, 7) == 0)
		return (3);
	else if (len_str == 2 && ft_strncmp("cd\0", str, 3) == 0)
		return (4);
	else if (len_str == 5 && ft_strncmp("unset\0", str, 6) == 0)
		return (5);
	else if (len_str == 4 && ft_strncmp("echo\0", str, 5) == 0)
		return (6);
	else if (len_str == 4 && ft_strncmp("exit", str, 4) == 0)
		return (7);
	return (0);
}

int	dispatch_builtins(t_data *data, char **str, int which)
{
	if (which == 0)
		return (0);
	if (which == 1)
		cmd_pwd(data);
	else if (which == 2)
		cmd_env(data, str);
	else if (which == 3)
		cmd_export(data, str);
	else if (which == 4)
		cmd_cd(data, str);
	else if (which == 5)
		cmd_unset(data, str, 0);
	else if (which == 6)
		cmd_echo(str);
	else if (which == 7)
		cmd_exit(data, str);
	if (data->nb_cmd_node == 1 && (which == 3 || which == 4 || which == 5
			|| which == 7))
		return (g_exit_s);
	else
		exit(g_exit_s);
}
