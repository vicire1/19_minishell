/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:05:01 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/07 14:24:23 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
    char *line;
    (void)ac;
    (void)av;
    (void)envp;
    
    while (1)
    {
        line = readline("minishell: ");
        if (!line)
            break;
        add_history(line);
        lexer(line);
        // free
    }
}