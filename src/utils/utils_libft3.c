/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:04:44 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/08 13:08:00 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if ((str1[0] == 0 && str2[0] == 0) || n == 0)
		return (0);
	while (str1[i] == str2[i] && n > i && str1[i] && str2[i])
		i++;
	if (i == n || str1[i] == str2[i])
		return (0);
	if (str1[i] >= 0 && str2[i] >= 0 && str2[i] > str1[i])
		return (-1);
	else
		return (1);
}

char	*ft_strdup(const char *s, t_data *data)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ret)
		free_all(data, ERR_MAL, 1);
	while (s[i] != 0)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dstsize - 1 > i && src[i] != 0 && dstsize != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = 0;
	return ((size_t)ft_strlen(src));
}

char	*ft_strjoin_bis(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	size_s1;
	size_t	size_s2;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	ret = malloc((size_s1 + size_s2 + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, size_s1 + 1);
	i = size_s1;
	while (i < size_s1 + size_s2)
	{
		ret[i] = s2[j++];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2, t_data *data)
{
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	size_s1;
	size_t	size_s2;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	ret = malloc((size_s1 + size_s2 + 1) * sizeof(char));
	if (!ret)
		free_all(data, ERR_MAL, 1);
	ft_strlcpy(ret, s1, size_s1 + 1);
	i = size_s1;
	while (i < size_s1 + size_s2)
	{
		ret[i] = s2[j++];
		i++;
	}
	ret[i] = 0;
	return (ret);
}