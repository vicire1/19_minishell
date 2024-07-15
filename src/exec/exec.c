/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:16:06 by vdecleir          #+#    #+#             */
/*   Updated: 2024/07/15 18:19:16 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_abs_path(t_data *data, char *cmd)
{
	char	*abs_path;
	int		i;
	char	*temp;

	abs_path = NULL;
	if (access(cmd, X_OK) == 0)
		abs_path = ft_strdup(cmd, data);
	else if (data->poss_path)
	{
		i = 0;
		while (data->poss_path[i])
		{
			temp = ft_strjoin(data->poss_path[i], cmd, data);
			if (access(temp, X_OK) == 0)
			{
				abs_path = temp;
				return (abs_path);
			}
			free(temp);
			temp = NULL;
			i++;
		}
	}
	return (abs_path);
}

void	ft_child_exec(t_data *data, int pfd[2], int i, int prev_fd)
{
	t_pars	*current;
	char	*abs_path;

	current = data->first_pars;
	close(pfd[0]);
	if (i != 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i != data->nb_cmd_node - 1)
	{
		dup2(pfd[1], STDOUT_FILENO);
	}
	close(pfd[1]);
	while (i-- > 0)
		current = current->next;
	open_redir(current->redir);
	dispatch_builtins(data, current->cmd, check_if_builtin(current->cmd[0]));
	abs_path = find_abs_path(data, current->cmd[0]);
	if (!abs_path)
	{
		ft_printf_fd(2, "%s: command not found\n", current->cmd[0]);
		exit(1);
	}
	execve(abs_path, current->cmd, data->env_arr);
}

int	executor(t_data *data)
{
	int	pfd[2];
	int	i;
	int	prev_fd;

	i = -1;
	prev_fd = -1;
	if (data->nb_cmd_node == 1 && ())
	while (++i < data->nb_cmd_node)
	{
		env_in_array(data);
		if (pipe(pfd) == -1)
			free_all(data, ERR_PIP, 1);
		data->pid = fork();
		if (data->pid == -1)
			free_all(data, ERR_FORK, 1);
		if (data->pid == 0)
			ft_child_exec(data, pfd, i, prev_fd);
		close(prev_fd);
		prev_fd = pfd[0];
		close(pfd[1]);
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
