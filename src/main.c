/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:05:01 by vdecleir          #+#    #+#             */
/*   Updated: 2024/06/04 18:08:55 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_data(t_data *data)
{
	data->pos = -1;
	data->first = NULL;
	data->first_pars = NULL;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char*	line;
	t_data	data;

	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		init_data(&data);
		line = readline("minishell: ");
		if (lexer(line, &data))
			printf("%s\n", ERR_SYN);
		parser(&data);
		add_history(line);
		free(line);
		free_all(&data, NULL, 0);
	}
}
