/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:05:01 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/07 16:33:04 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
    char *line;
    (void)ac;
    (void)av;
    (void)envp;
    t_data data;
    while (1)
    {
        line = readline("minishell: ");
        
        lexer(&data);
    }
}