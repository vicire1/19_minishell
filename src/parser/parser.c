/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:16:19 by vdecleir          #+#    #+#             */
/*   Updated: 2024/06/04 19:25:50 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd(char **cmd)
{
	int	i = 0;
	
	printf("CMD : \n");
	while (cmd[i])
	{
		printf("%s ", cmd[i]);
		i++;
	}
	printf("\n");
}

void	print_redir(t_redir *redir)
{
	t_redir	*temp = redir;

	printf("REDIR : \n");
	if (!temp)
		return ;
	while (temp->next)
	{
		printf("%d      ", temp->token);
		printf("%s\n", temp->file);
		temp = temp->next;
	}
	printf("%d      ", temp->token);
	printf("%s\n", temp->file);
}

void	print_pars(t_pars *first)
{
	t_pars	*temp = first;
	
	while (temp->next)
	{
		printf("---------------------------------\n");
		print_cmd(temp->cmd);
		printf("nb redir : %d\n", temp->nb_redir);
		print_redir(temp->redir);
		printf("---------------------------------\n");
		temp = temp->next;
	}
	printf("---------------------------------\n");
	print_cmd(temp->cmd);
	printf("nb redir : %d\n", temp->nb_redir);
	print_redir(temp->redir);
	printf("---------------------------------\n");
}

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
	t_redir		*new;
	t_pars		*pars_node;
	t_redir		*temp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->token = token;
	new->file = ft_strdup(file_node->token_str);
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

void	create_redir_lst(t_data *data, t_lexer *start, int redir)
{
	t_lexer	*current;
	t_redir	*new;
	int		token;
	int		i;
	
	i = 0;
	current = start;
	while (i < redir)
	{
		if (current->token)
		{
			token = current->token;
			current = current->next;
			new = init_redir_node(data, current, token, i);
			if (i == 0)
				add_redir_to_pars(data->first_pars, new);
			i++;
		}
		current = current->next;
	}
}

char **create_cmd(t_lexer *start, int arg)
{
	t_lexer	*temp;
	char	**cmd;
	int		i;

	cmd = malloc(sizeof(char **) * (arg + 1));
	if (!cmd)
		//freeexit
		return (NULL);
	i = 0;
	temp = start;
	while (i < arg)
	{
		if (temp->token)
			temp = temp->next;
		else
		{
			cmd[i] = ft_strdup(temp->token_str);
			i++;
		}
		temp = temp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

int new_node_pars(t_data *data, t_lexer *start, int arg, int redir)
{
    t_pars		*new;
	t_pars		*temp;

	new = malloc(sizeof(t_pars));
	if (!new)
		return (-1);
	new->cmd = create_cmd(start, arg);
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

int	parser(t_data *data)
{
	t_lexer *current;
    t_lexer *start;
    int     arg;
    int     redir;

    current = data->first;
    if (current->token == 1)
    {
        // free et return bon truc
        return (-1);
    }
    while (current)
    {
        arg = 0;
        redir = 0;
        start = current;
        while (current)
        {
            if (current->token == 1)
            {
                current = current->next;
                break;
            }
            else if (current->token)
			{
                redir++;
				current = current->next;
			}
			else
            	arg++;
            current = current->next;
        }
        new_node_pars(data, start, arg, redir);
		create_redir_lst(data, start, redir);
    }
	print_pars(data->first_pars);
	return (0);
}
