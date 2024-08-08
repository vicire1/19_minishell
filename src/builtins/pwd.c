/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:09:50 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/08 14:14:43 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cmd_pwd(t_data *data)
{
	char	*pwd;
	t_env	*tempo;

	tempo = data->first_env;
	pwd = getcwd(NULL, 0);
	if (pwd)
		ft_printf_fd(1, "%s\n", pwd);
	else
	{
		while (tempo)
		{
			if (ft_strncmp(tempo->name, "PWD=", 4) == 0)
			{
				ft_printf_fd(1, "%s\n", tempo->value);
				break ;
			}
			tempo = tempo->next;
		}
	}
	if (pwd)
		free(pwd);
	g_exit_s = 0;
	return ;
}
