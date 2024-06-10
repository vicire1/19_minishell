/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:38:20 by vdecleir          #+#    #+#             */
/*   Updated: 2024/06/10 17:20:43 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    free_cmd_arr(char **cmd)
{
    int i;

    i = -1;
    while (cmd[++i])
    {
        free(cmd[i]);
        cmd[i] = NULL;
    }
    free(cmd);
    cmd = NULL;
}

void    free_redir_lst(t_redir *redir)
{
    t_redir *current;
    t_redir *temp;

    current = redir;
    while (current)
    {
        free(current->file);
        current->file = NULL;
        temp = current;
        current = current->next;
        free(temp);
    }
}

int free_all(t_data *data, char *str, int esc)
{
    t_pars *current;
    t_pars *temp;

    if (str)
        ft_printf_fd(2, "%s\n", str);
    free_lex(data);
    free_exp(data);
    current = data->first_pars;
    if (current)
    {
        while (current)
        {
            free_cmd_arr(current->cmd);
            free_redir_lst(current->redir);
            temp = current;
            current = current->next;
            free(temp);
        }
    }
    if (esc)
        exit (esc);
    return (0);
}
