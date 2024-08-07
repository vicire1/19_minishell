/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:42:40 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/06 15:49:07 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unlink_heredoc(t_data *data)
{
	char	*path;
	int		i;
	char	*nb_i;

	i = -1;
	nb_i = ft_itoa(++i, data);
	path = ft_strjoin("/tmp/.tmp_hd_", nb_i, data);
	while (access(path, F_OK) == 0)
	{
		unlink(path);
		free(nb_i);
		free(path);
		nb_i = ft_itoa(++i, data);
		path = ft_strjoin("/tmp/.tmp_hd_", nb_i, data);
	}
	free(nb_i);
	free(path);
}

void	open_heredoc(t_pars *current, char *eof)
{
	int		fd;
	char	*line;
	size_t	n;

	fd = open(current->hdoc, O_CREAT | O_RDWR | O_TRUNC, 0644);
	n = ft_strlen(eof);
	line = readline("> ");
	while (ft_strncmp(line, eof, n) != 0 || n != ft_strlen(line))
	{
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd);
}

void	check_heredoc(t_data *data)
{
	t_pars	*current;
	t_redir	*redir;
	int		i;
	char	*nb_i;

	i = -1;
	current = data->first_pars;
	while (current)
	{
		redir = current->redir;
		while (redir)
		{
			if (redir->token == 5)
			{
				nb_i = ft_itoa(++i, data);
				if (current->hdoc)
					free(current->hdoc);
				current->hdoc = ft_strjoin("/tmp/.tmp_hd_", nb_i, data);
				free(nb_i);
				open_heredoc(current, redir->file);
			}
			redir = redir->next;
		}
		current = current->next;
	}
}
