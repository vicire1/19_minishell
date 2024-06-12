/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:05:01 by vdecleir          #+#    #+#             */
/*   Updated: 2024/06/12 15:08:15 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_data(t_data *data)
{
	data->first_lex = NULL;
	data->first_pars = NULL;
	return (0);
}

int	init_env(t_data	*data, char **envp)
{
	int	i;

	i = 0;
	data->first_env = NULL;
	while(envp[i])
	{
		new_node_env(envp[i], data);
		i++;
	}
	print_env(data);
	return(0);
}

int	main(int ac, char **av, char **envp)
{
	char*	line;
	t_data	data;

	(void)ac;
	(void)av;
	init_env(&data, envp);
	while (1)
	{
		init_data(&data);
		line = readline("minishell: ");

		printf("%s\n", line);

		if (lexer(line, &data))
			printf("%s\n", ERR_SYN);
		else
		{
			expander(&data);
			parser(&data);
		}
		add_history(line);
		free(line);
		free_all(&data, NULL, 0);
	}
}
