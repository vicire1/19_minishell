/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:09:55 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/08 13:09:56 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset_env_node(t_data *data, t_env *tempo)
{
	if (tempo->prev == NULL)
	{
		data->first_env = (t_env *)tempo->next;
		if (tempo->next != NULL)
			((t_env *)tempo->next)->prev = NULL;
	}
	else
	{
		((t_env *)tempo->prev)->next = tempo->next;
		if (tempo->next != NULL)
			((t_env *)tempo->next)->prev = tempo->prev;
	}
	free(tempo->name);
	tempo->name = NULL;
	if (tempo->value)
	{
		free(tempo->value);
		tempo->value = NULL;
	}
	free(tempo);
	return ;
}

void	cmd_unset_do_it(t_data *data, char *str, int size_str, int size_name)
{
	t_env	*tempo;

	tempo = data->first_env;
	size_str = ft_strlen(str);
	while (tempo)
	{
		size_name = ft_strlen(tempo->name);
		if (((size_name - 1) == size_str)
			&& ft_strncmp(tempo->name, str, size_str) == 0)
		{
			unset_env_node(data, tempo);
			return ;
		}
		tempo = (t_env *)tempo->next;
	}
}

int	cmd_unset_sec_chek_in_env(t_data *data, char *str)
{
	t_env	*tempo;

	tempo = data->first_env;
	while (tempo)
	{
		if ((tempo->env_status == 0
				&& (ft_strncmp(str, tempo->name, ft_strlen(str)) == 0))
			&& ft_strlen(tempo->name) == ft_strlen(str))
			return (1);
		tempo = tempo->next;
	}
	return (0);
}

void	cmd_unset_do_it_sec(t_data *data, char *str, int size_str)
{
	t_env	*tempo;

	tempo = data->first_env;
	size_str = ft_strlen(str);
	while (tempo)
	{
		if (tempo->env_status == 0
			&& (ft_strncmp(str, tempo->name, size_str) == 0))
		{
			unset_env_node(data, tempo);
			return ;
		}
		tempo = (t_env *)tempo->next;
	}
}

void	cmd_unset(t_data *data, char **str, int i)
{
	char	*tmp;

	if (!str[1])
		return ;
	i = 1;
	while (str[i])
	{
		if (cmd_unset_check_in_env(data, str[i]))
		{
			cmd_unset_do_it(data, str[i], 0, 0);
			if (cmd_unset_check_in_env(data, str[i]))
			{
				tmp = ft_substr(str[i], 0, ft_strlen(str[i]) - 1, data);
				cmd_unset_do_it(data, tmp, 0, 0);
				free(tmp);
			}
		}
		else if (cmd_unset_check_invalid(str[i]))
			ft_printf_fd(2,
				"minishell: unset : `%s\': not a valid identifier\n", str[i]);
		else if (cmd_unset_sec_chek_in_env(data, str[i]))
			cmd_unset_do_it_sec(data, str[i], 0);
		i++;
	}
	return ;
}
