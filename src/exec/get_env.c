/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:41:17 by vdecleir          #+#    #+#             */
/*   Updated: 2024/07/11 21:55:52 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_lstlen(t_env *lst)
{
    int i;

    i = 0;
    while (lst)
    {
        if (lst->value)
            i++;
        lst = lst->next;
    }
    return (i);
}

static char	**put_slash(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (data->poss_path[i])
	{
		temp = ft_strjoin(data->poss_path[i], "/", data);
		free(data->poss_path[i]);
		data->poss_path[i] = temp;
		i++;
	}
	return (data->poss_path);
}

char **get_poss_path(t_data *data, int array_size)
{
    t_env   *current;

    current = data->first_env;
    data->poss_path = malloc(sizeof(char *) * array_size);
    if (!data->poss_path)
        free_all(data, ERR_MAL, 1);
    while (current)
    {
        if (ft_strncmp(current->name, "PATH=\0", 6) == 0)
        {
            data->poss_path = ft_split(current->value, ':', data);
            put_slash(data);
            break;
        }
        current = current->next;
    }
    return (data->poss_path);
}

char    **env_in_array(t_data *data)
{
    t_env   *current;
    int     env_len;
    int     i;

    current = data->first_env;
    env_len = ft_lstlen(current);
    i = -1;
    if (env_len == 0)
        return (NULL);
    data->env_arr = malloc(sizeof(char *) * (env_len + 1));
    if (!data->env_arr)
        free_all(data, ERR_MAL, 1);
    while (current)
    {
        if (current->value)
            data->env_arr[++i] = ft_strjoin(current->name, current->value, data);
        current = current->next;
    }
    data->env_arr[i] = NULL;
    get_poss_path(data, i);
    return(data->env_arr);
}
