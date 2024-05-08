/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:05:01 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/08 19:33:57 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int init_data(t_data *data)
{
    data->pos = -1;
    data->first = NULL;
    return (0);
}

int main(int ac, char **av, char **envp)
{
    char *line;
    (void)ac;
    (void)av;
    (void)envp;
    t_data data;

    while (1)
    {
        init_data(&data);
        line = readline("minishell : ");
        if (lexer(line, &data))
            printf("%s\n", ERR_SYN);
        add_history(line);
        free(line);
        free_all(&data, NULL, 0);
    }
}
