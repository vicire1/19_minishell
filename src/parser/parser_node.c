/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:03:22 by vdecleir          #+#    #+#             */
/*   Updated: 2024/06/10 17:18:40 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_redir_to_pars(t_pars *first_pars, t_redir *first_redir)
{
	t_pars	*current;

	current = first_pars;
	while (current->next)
		current = current->next;
	current->redir = first_redir;
}

t_redir	*init_redir_node(t_data *data, t_lexer *file_node, int token, int i)
{
	t_redir	*new;
	t_pars	*pars_node;
	t_redir	*temp;

	new = malloc(sizeof(t_redir));
	if (!new)
		free_all(data, ERR_MAL, 1);
	new->token = token;
	new->file = ft_strdup(file_node->token_str, data);
	if (!new->file)
		free_all(data, ERR_MAL, 1);
	new->next = NULL;
	if (i == 0)
		return (new);
	pars_node = data->first_pars;
	while (pars_node->next)
		pars_node = pars_node->next;
	temp = pars_node->redir;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (new);
}

int	new_node_pars(t_data *data, t_lexer *start, int arg, int redir)
{
	t_pars	*new;
	t_pars	*temp;

	new = malloc(sizeof(t_pars));
	if (!new)
		free_all(data, ERR_MAL, 1);	
	new->cmd = create_cmd(data, start, arg);
	new->redir = NULL;
	new->nb_redir = redir;
	new->next = NULL;
	if (data->first_pars == NULL)
	{
		new->prev = NULL;
		data->first_pars = new;
		return (0);
	}
	temp = data->first_pars;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	return (0);
}
