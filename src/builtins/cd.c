/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:09:37 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/08 13:09:38 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*cmd_cd_home_get_home(t_data *data)
{
	t_env	*tempo;

	tempo = data->first_env;
	while (tempo)
	{
		if (ft_strncmp("HOME=", tempo->name, 5) == 0
			&& ft_strlen(tempo->name) == 5)
			return (ft_strdup(tempo->value, data));
		tempo = tempo->next;
	}
	return (NULL);
}

void	cmd_cd_home(t_data *data)
{
	char	*home_path;

	home_path = cmd_cd_home_get_home(data);
	if (!home_path)
	{
		ft_printf_fd(2, "minishell: cd: HOME not set\n");
		g_exit_s = 1;
		return ;
	}
	if (access(home_path, F_OK) == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n",
			home_path);
		return ;
	}
	if (access(home_path, X_OK) == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: Permission denied\n", home_path);
		g_exit_s = 1;
		return ;
	}
	cmd_cd_change_oldpwd(data, cmd_cd_home_get_new_oldpwd(data),
		NULL, NULL);
	chdir(home_path);
	cmd_cd_change_pwd(data, home_path);
}

/**
 * @brief Hendle the 'cd' command with path
 * 
 * @param data struct data
 * @param str arg
 */
void	cmd_cd_path(t_data *data, char *str)
{
	if (cmd_cd_path_file_or_dir_err(str))
	{
		if (ft_strlen(str) == 2 && ft_strncmp("..", str, 2) == 0)
			cmd_cd_home(data);
		return ;
	}
	cmd_cd_change_oldpwd(data, cmd_cd_home_get_new_oldpwd(data),
		NULL, NULL);
	chdir(str);
	cmd_cd_change_pwd(data, getcwd(NULL, 0));
	return ;
}

void	cmd_cd_dash(t_data *data)
{
	char	*oldpwd_tmp;
	t_env	*tmp;

	oldpwd_tmp = NULL;
	tmp = data->first_env;
	while (tmp)
	{
		if (ft_strncmp("OLDPWD=", tmp->name, 7) == 0
			&& ft_strlen(tmp->name) == 7)
		{
			oldpwd_tmp = ft_strdup(tmp->value, data);
			break ;
		}
		tmp = tmp->next;
	}
	if (!cmd_cd_path_file_or_dir_err(oldpwd_tmp))
	{
		cmd_cd_change_oldpwd(data, cmd_cd_home_get_new_oldpwd(data),
			NULL, NULL);
		chdir(oldpwd_tmp);
		cmd_cd_change_pwd(data, getcwd(NULL, 0));
		free(oldpwd_tmp);
		g_exit_s = 0;
	}
}

/**
 * @brief Handles the 'cd' command to change the current directory.
 * 
 * @param data struct data
 * @param str [0] => cd [.;.;.]=> arg
 */
void	cmd_cd(t_data *data, char **str)
{
	int	len_str2;

	len_str2 = ft_strlen(str[1]);
	if (!str[1])
		cmd_cd_home(data);
	else if (len_str2 == 1 && ft_strncmp("-", str[1], 1) == 0)
		cmd_cd_dash(data);
	else if (len_str2 == 2 && ft_strncmp("--", str[1], 2) == 0)
		cmd_cd_home(data);
	else if (len_str2 == 1 && ft_strncmp(".", str[1], 1) == 0)
		cmd_cd_change_oldpwd(data, cmd_cd_home_get_new_oldpwd(data),
			NULL, NULL);
	else
		cmd_cd_path(data, str[1]);
	return ;
}
