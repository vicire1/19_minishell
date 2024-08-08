/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:59:08 by lbirloue          #+#    #+#             */
/*   Updated: 2024/08/08 13:34:28 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	free_lex(t_data *data)
{
	t_lexer	*current;
	t_lexer	*temp;

	current = data->first_lex;
	while (current)
	{
		free(current->token_str);
		temp = current;
		current = current->next;
		free(temp);
	}
	return (0);
}

void	free_arr(char **cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return ;
	while (cmd[++i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
	}
	free(cmd);
	cmd = NULL;
}

void	free_redir_lst(t_redir *redir)
{
	t_redir	*current;
	t_redir	*temp;

	current = redir;
	while (current)
	{
		free(current->file);
		current->file = NULL;
		temp = current;
		current = current->next;
		free(temp);
	}
}

void	free_pars(t_data *data)
{
	t_pars	*current;
	t_pars	*temp;

	current = data->first_pars;
	while (current)
	{
		free_arr(current->cmd);
		free_redir_lst(current->redir);
		free(current->hdoc);
		temp = current;
		current = current->next;
		free(temp);
	}
}

void	free_env(t_data *data)
{
	t_env	*current;
	t_env	*temp;

	current = data->first_env;
	while (current)
	{
		free(current->name);
		free(current->value);
		temp = current;
		current = current->next;
		free(temp);
	}
	return ;
}
