/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:16:06 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/08 13:36:55 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_abs_path(t_data *data, char *cmd)
{
	char	*abs_path;
	int		i;
	char	*temp;

	abs_path = NULL;
	if (data->poss_path)
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
	else if (access(cmd, X_OK) == 0)
		abs_path = ft_strdup(cmd, data);
	return (abs_path);
}

void	ft_child_exec(t_data *data, int pfd[2], int i, int prev_fd)
{
	t_pars	*current;
	char	*abs_path;

	current = data->first_pars;
	if (i != 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i != data->nb_cmd_node - 1)
		dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	while (i-- > 0)
		current = current->next;
	open_redir(current);
	if (!current->cmd[0])
		exit(0);
	dispatch_builtins(data, current->cmd, check_if_builtin(current->cmd[0]));
	abs_path = find_abs_path(data, current->cmd[0]);
	if (!abs_path)
	{
		ft_printf_fd(2, "%s: command not found\n", current->cmd[0]);
		exit(1);
	}
	execve(abs_path, current->cmd, data->env_arr);
}

void	one_cmd_env(t_data *data, int bltn)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	open_redir(data->first_pars);
	dispatch_builtins(data, data->first_pars->cmd, bltn);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

void	multiple_cmd(t_data *data)
{
	int	pfd[2];
	int	prev_fd;
	int	i;

	i = -1;
	prev_fd = -1;
	while (++i < data->nb_cmd_node)
	{
		if (pipe(pfd) == -1)
			free_all(data, ERR_PIP, 1);
		data->pid = fork();
		if (data->pid == -1)
			free_all(data, ERR_FORK, 1);
		if (data->pid == 0)
		{
			close(pfd[0]);
			ft_child_exec(data, pfd, i, prev_fd);
		}
		close(prev_fd);
		prev_fd = pfd[0];
		close(pfd[1]);
	}
}

int	executor(t_data *data)
{
	int	bltn;
	int	status;

	env_in_array(data);
	bltn = check_if_builtin(data->first_pars->cmd[0]);
	check_heredoc(data);
	if (data->nb_cmd_node == 1 && (bltn == 3 || bltn == 4 || bltn == 5
			|| bltn == 7))
	{
		one_cmd_env(data, bltn);
		return (0);
	}
	else
		multiple_cmd(data);
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		g_exit_s = WEXITSTATUS(status);
	unlink_heredoc(data);
	return (0);
}
