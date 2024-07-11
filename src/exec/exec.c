/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:16:06 by vdecleir          #+#    #+#             */
/*   Updated: 2024/07/11 17:18:04 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ft_child_exec(t_data *data, int pfd[2], int i, int in_fd)
{
    t_pars *current;

    current = data->first_pars;
    if (i != 0)
    {
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[0]);
    }
	if (i != data->nb_cmd_node - 1)
	{
		dup2(pfd[1], STDOUT_FILENO);
	    close(pfd[1]);
	}
    while (i-- >= 0)
        current = current->next;
    if (open_redir(current->redir))
        exit(1);
    
}

int executor(t_data *data)
{
    int     pfd[2];
    int     i;
    int     in_fd;

    i = -1;
    in_fd = STDIN_FILENO;
    while (++i < data->nb_cmd_node)
    {
        if (pipe(pfd) == -1)
            free_all(data, ERR_PIP, 1);
        data->pid = fork();
        if (data->pid == -1)
            free_all(data, ERR_FORK, 1);
        if (data->pid == 0)
            ft_child_exec(data, pfd, i, in_fd);
    }
}
