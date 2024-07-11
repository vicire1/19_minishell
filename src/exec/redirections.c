/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:54:25 by vdecleir          #+#    #+#             */
/*   Updated: 2024/07/11 15:53:05 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     outfile_redir(char *outfile)
{
    int fd;

    fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
    {
        ft_printf_fd(2, "%s: Error.\n", outfile);
        return (1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (0);
}

int     outfile_append_redir(char *outfile)
{
    int fd;

    fd = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
    if (fd < 0)
    {
        ft_printf_fd(2, "%s: Error.\n", outfile);
        return (1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (0);
}

int     infile_redir(char *infile)
{
    int fd;
    
    fd = open(infile, O_RDONLY);
    if (fd < 0)
    {
        ft_printf_fd(2, "%s: No such file or directory\n", infile);
        return(1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (0);
}

int    open_redir(t_redir *redir)
{
    t_redir *current;
    
    current = redir;
    while(current)
    {
        if (current->token == 2)
        {
            if (outfile_redir(current->file))
                return (1);
        }
        if (current->token == 3)
        {
            if (outfile_append_redir(current->file))
                return (1);
        }
        if (current->token == 4)
        {
            if (infile_redir(current->file))
                return (1);
        }
        current = current->next;
    }
    return (0);
}
