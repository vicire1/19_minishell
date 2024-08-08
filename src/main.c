/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:05:01 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/08 15:57:01 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_data(t_data *data)
{
	data->first_lex = NULL;
	data->first_pars = NULL;
	data->expa = NULL;
	data->env_arr = NULL;
	data->poss_path = NULL;
	data->nb_cmd_node = 0;
	return (0);
}

void	init_global(void)
{
	if (g_exit_s == 0)
		g_exit_s = 0;
	else if ((g_exit_s % 255) == 0)
		g_exit_s = 255;
	else if (g_exit_s > 255)
		g_exit_s = g_exit_s % 255;
}

void	process(t_data *data)
{
	char	*line;

	init_global();
	handle_sig(SIG_OUT_CHILD);
	init_data(data);
	line = readline("minishell: ");
	if (!line)
	{
		g_exit_s = 0;
		free_all(data, "minishell: exit", 1);
	}
	if (line && line[0] != '\0')
	{
		if (lexer(line, data))
			printf("%s\n", ERR_SYN);
		else if (data->first_lex)
		{
			expander(data);
			parser(data);
		}
		add_history(line);
		free(line);
		free_all(data, NULL, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_env(&data, envp);
	while (1)
		process(&data);
	return (0);
}
