/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:24:53 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 17:45:01 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_strchr_gnl(char *s, size_t c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2, size_t j)
{
	size_t	i;
	char	*ret;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	ret = malloc(sizeof(char) * ((ft_strlen_gnl(s1) + ft_strlen_gnl(s2)) + 1));
	if (ret == NULL)
		return (NULL);
	i = -1;
	if (s1)
		while (s1[++i] != '\0')
			ret[i] = s1[i];
	while (s2[j] != '\0')
		ret[i++] = s2[j++];
	ret[ft_strlen_gnl(s1) + ft_strlen_gnl(s2)] = '\0';
	free(s1);
	return (ret);
}

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}
