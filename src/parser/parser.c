/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:16:19 by vdecleir          #+#    #+#             */
/*   Updated: 2024/06/12 15:09:04 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd(char **cmd)
{
	int	i;

	i = 0;
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
	t_redir	*temp;

	temp = redir;
	printf("REDIR : \n");
	while (temp)
	{
		printf("%d      ", temp->token);
		printf("%s\n", temp->file);
		temp = temp->next;
	}
}

void	print_pars(t_pars *first)
{
	t_pars	*temp;

	temp = first;
	while (temp)
	{
		printf("---------------------------------\n");
		print_cmd(temp->cmd);
		printf("nb redir : %d\n", temp->nb_redir);
		print_redir(temp->redir);
		printf("---------------------------------\n");
		temp = temp->next;
	}
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

char	**create_cmd(t_data *data, t_lexer *start, int arg)
{
	t_lexer	*temp;
	char	**cmd;
	int		i;

	cmd = malloc(sizeof(char **) * (arg + 1));
	if (!cmd)
		free_all(data, ERR_MAL, 1);
	i = 0;
	temp = start;
	while (i < arg)
	{
		if (temp->token)
			temp = temp->next;
		else
		{
			cmd[i] = ft_strdup(temp->token_str, data);
			i++;
		}
		temp = temp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

t_lexer	*count_redir(t_lexer *current, int *arg, int *redir)
{
	while (current)
	{
		if (current->token == 1)
		{
			current = current->next;
			break ;
		}
		else if (current->token)
		{
			(*redir)++;
			current = current->next;
		}
		else
			(*arg)++;
		current = current->next;
	}
	return (current);
}

int	parser(t_data *data)
{
	t_lexer	*current;
	t_lexer	*start;
	int		arg;
	int		redir;

	current = data->first_lex;
	if (current->token == 1)
	{
		printf("%s\n", ERR_SYN);
		return (1);
	}
	while (current)
	{
		arg = 0;
		redir = 0;
		start = current;
		current = count_redir(current, &arg, &redir);
		new_node_pars(data, start, arg, redir);
		create_redir_lst(data, start, redir);
	}
	print_pars(data->first_pars);
	return (0);
}
