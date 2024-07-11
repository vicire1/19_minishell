/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:05:01 by vdecleir          #+#    #+#             */
/*   Updated: 2024/07/11 17:22:36 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_data(t_data *data)
{
	data->first_lex = NULL;
	data->first_pars = NULL;
	data->expa = NULL;
	return (0);
}

int	init_env(t_data	*data, char **envp)
{
	int	i;

	i = 0;
	data->first_env = NULL;
	while(envp[i])
	{
		new_node_env(envp[i], 1, data);
		i++;
	}
	init_export(data);
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
		if (line && line[0] != '\0')
		{
			if (lexer(line, &data))
				printf("%s\n", ERR_SYN);
			else
			{
				expander(&data);
				parser(&data);
			}
			t_pars	*temp;

			temp = data.first_pars;
			while (temp)
			{
			int	i;

			i = 0;
			while (temp->cmd[i])
			{
				int	which = check_if_builtin(temp->cmd[i]);
				dispatch_builtins(&data, temp->cmd, 0, which);
				i++;
			}
			temp = temp->next;
			}
			add_history(line);
			free(line);
			free_all(&data, NULL, 0);
		}
	}
}


// int	main(int ac, char **av, char **envp)
// {
// 	char*	line;
// 	t_data	data;

// 	(void)ac;
// 	(void)av;
// 	init_env(&data, envp);
// 	// while (1)
// 	// {
// 		init_data(&data);
// 		// line = readline("minishell: ");
// 		line = ft_strdup("$USER$non\'$USER\' $USER$non $USER non$USER\'non\'$   \"$\" $ \'$\' ", &data);
// 		printf("%s\n", line);

// 		if (lexer(line, &data))
// 			printf("%s\n", ERR_SYN);

// 		else
// 		{
// 			expander(&data);
// 			parser(&data);
// 		}
// 		// add_history(line);
// 		free(line);
		
// 		free_env(&data);
		
// 		free_all(&data, NULL, 0);
// 	// }
// }


