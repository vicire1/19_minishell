/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:38:44 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 17:44:53 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*gnl2(int fd, char *tempo)
{
	char	*str;
	ssize_t	i;

	i = 1;
	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (!ft_strchr_gnl(tempo, '\n') && i != 0)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i == -1)
		{
			free(tempo);
			free(str);
			return (NULL);
		}
		str[i] = '\0';
		tempo = ft_strjoin_gnl(tempo, str, 0);
	}
	free(str);
	return (tempo);
}

char	*next_line(char *tempo)
{
	char	*ret;
	int		i;

	i = 0;
	if (!tempo[i])
		return (NULL);
	while (tempo[i] != '\n' && tempo[i])
		i++;
	ret = malloc(sizeof(char) * (i + 2));
	if (!ret)
		return (NULL);
	i = 0;
	while (tempo[i] != '\n' && tempo[i])
	{
		ret[i] = tempo[i];
		i++;
	}
	if (tempo[i] == '\n')
	{
		ret[i] = tempo[i];
		i += 1;
	}
	ret[i] = '\0';
	return (ret);
}

char	*refresh(char *tempo)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tempo[i] != '\n' && tempo[i])
		i++;
	if (!tempo[i])
	{
		free(tempo);
		return (NULL);
	}
	ret = malloc(sizeof(char) * (ft_strlen_gnl(tempo) - i + 1));
	i += 1;
	if (!ret)
		return (NULL);
	while (tempo[i] != '\0')
		ret[j++] = tempo[i++];
	ret[j] = '\0';
	free(tempo);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*tempo[OPEN_MAX];
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	tempo[fd] = gnl2(fd, tempo[fd]);
	if (!tempo[fd])
		return (NULL);
	ret = next_line(tempo[fd]);
	tempo[fd] = refresh(tempo[fd]);
	return (ret);
}
