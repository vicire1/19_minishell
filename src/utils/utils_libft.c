/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:58:39 by vdecleir          #+#    #+#             */
/*   Updated: 2024/06/07 12:39:06 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len, t_data *data)
{
	unsigned int	i;
	char			*ret;

	i = 0;
	if (!s)
		return (0);
	while (i < len && start + i < ft_strlen(s))
		i++;
	ret = malloc((i + 1) * sizeof(char));
	if (!ret)
		free_all(data, ERR_MAL, 1);
	i = 0;
	while (len > i && start + i < ft_strlen(s))
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	is_white_space(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

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

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ret)
		return (0);
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

char	*ft_strjoin(char const *s1, char const *s2)
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
		return (0);
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
