/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:09:42 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/08 14:14:30 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmd_env_check_arg(char *str)
{
	if (!str)
		return (0);
	if (str[1] == '-')
	{
		ft_printf_fd(2, "No option allowed for env\n");
		g_exit_s = 1;
		return (1);
	}
	ft_printf_fd(2, "No argument allowed for env\n");
	g_exit_s = 1;
	return (1);
}

void	cmd_env(t_data *data, char **str)
{
	t_env	*tempo;

	tempo = data->first_env;
	if (cmd_env_check_arg(str[1]))
		return ;
	while (tempo)
	{
		if (tempo->env_status)
		{
			if (tempo->name && tempo->value)
				ft_printf_fd(1, "%s%s\n", tempo->name, tempo->value);
			else
				ft_printf_fd(1, "%s\n", tempo->name);
		}
		tempo = tempo->next;
	}
	g_exit_s = 0;
	return ;
}
