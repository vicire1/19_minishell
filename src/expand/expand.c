/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:16:09 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/13 18:00:53 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quotes(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			i f
		}
	}
	return (0);
}

int	del_quotes(char	**cmd)
{
	return (0);
}

int	expander(t_data *data)
{
	t_parser exp;

	exp = data->first_parser;

	while (exp->next)
	{
		if (check_quotes(exp->cmd) == 1)
		{
			if (del_quotes(exp->cmd) == -1)
				free_all_parser(exp, ERR_MAL, 1);
		}
	}
	return (0);
}
