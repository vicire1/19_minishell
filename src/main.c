/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:05:01 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/08 00:59:40 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int init_data(t_data *data)
// {
//     data->first = NULL;
//     return (0);
// }

int main(int ac, char **av, char **envp)
{
    char *line;
    (void)ac;
    (void)av;
    (void)envp;
    t_data data;

    // init_data(&data);
    while (1)
    {
        data.first = NULL;
        line = readline("minishell : ");
        lexer(line, &data);
        add_history(line);
        free_all(&data, line);
    }
}
