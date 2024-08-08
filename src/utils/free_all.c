/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:00:04 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/08 13:35:53 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	free_all(t_data *data, char *str, int esc)
{
	if (str)
		ft_printf_fd(2, "%s\n", str);
	free_lex(data);
	free_pars(data);
	free_arr(data->env_arr);
	free_arr(data->poss_path);
	if (esc)
	{
		unlink_heredoc(data);
		free_env(data);
		exit(g_exit_s);
	}
	return (0);
}
