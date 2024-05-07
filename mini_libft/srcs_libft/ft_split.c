/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:57:00 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 16:40:31 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	size_str(char const *s, char c, ssize_t i)
{
	size_t	ret;

	ret = 0;
	while (s[i] != c && s[i] != 0)
	{
		ret++;
		i++;
	}
	return (ret);
}

static int	str_count(char const *s, char c)
{
	size_t	i;
	int		j;

	j = 0;
	i = 0;
	while (s[i] != 0)
	{
		while (s[i] == c && s[i] != 0)
			i++;
		if (s[i] != 0)
		{
			while (s[i] && s[i] != c)
				i++;
			j++;
		}
		while (s[i] == c && s[i] != 0)
			i++;
	}
	return (j);
}

static char	**freeall(char **s, ssize_t i)
{
	while (i >= 0)
	{
		free(s[i]);
		s[i] = NULL;
		i--;
	}
	free(s);
	s = NULL;
	return (s);
}

static char	**split2(char const *s, char c, char **ret)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	count_str;
	unsigned int	len_str;

	i = 0;
	j = -1;
	count_str = str_count(s, c);
	while (s[i] != 0)
	{
		if (s[i] == c)
			while (s[i] == c)
				i++;
		else
		{
			len_str = size_str(s, c, i);
			ret[++j] = ft_substr(s, i, len_str);
			if (!ret[j])
				return (freeall(ret, j));
			i += len_str;
		}
	}
	ret[++j] = NULL;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	size_t	j;
	ssize_t	i;
	char	**ret;

	j = 0;
	i = 0;
	if (!s)
		return (0);
	ret = malloc((str_count(s, c) + 1) * sizeof(char *));
	if (!ret)
		return (0);
	return (split2(s, c, ret));
}
