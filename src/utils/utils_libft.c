/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:58:39 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/06 14:41:16 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_tabs(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[0] != c && s[0] != '\0')
	{
		count++;
		i++;
	}
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static int	split_strlen(char const *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i + count] != c && s[i + count])
		count++;
	return (count);
}

static int	cpy_in_tab(char **tab, char const *s, char c)
{
	int	a;
	int	b;
	int	i;

	a = 0;
	i = 0;
	while (a < count_tabs(s, c))
	{
		b = 0;
		while (s[i] == c && s[i])
			i++;
		tab[a] = malloc(sizeof(char) * (split_strlen(s, c, i) + 1));
		if (tab[a] == NULL)
			return (a);
		while (s[i] && s[i] != c)
		{
			tab[a][b] = s[i];
			b++;
			i++;
		}
		tab[a][b] = '\0';
		a++;
	}
	return (-1);
}

char	**ft_split(char const *s, char c, t_data *data)
{
	int		cpy;
	char	**tab;

	if (!s)
		return (0);
	tab = malloc(sizeof(char *) * (count_tabs(s, c) + 1));
	if (tab == NULL)
		free_all(data, ERR_MAL, 1);
	cpy = cpy_in_tab(tab, s, c);
	if (cpy != -1)
		free_all(data, ERR_MAL, 1);
	tab[count_tabs(s, c)] = 0;
	return (tab);
}

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

char	*ft_substr_bis(char const *s, unsigned int start, size_t len)
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
		return (NULL);
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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
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

static int	c_nbr(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i = i + 1;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*posint(int char_nbr, int n, char *ret)
{
	int		char_0;
	char	char_c;

	char_0 = char_nbr;
	while (char_nbr > 0)
	{
		char_c = ((n % 10) + 48);
		n = n / 10;
		ret[char_nbr - 1] = char_c;
		char_nbr--;
	}
	ret[char_0] = 0;
	return (ret);
}

static char	*negint(int char_nbr, int n, char *ret)
{
	int		char_0;
	char	char_c;

	char_0 = char_nbr;
	n = -n;
	while (char_nbr > 0)
	{
		char_c = ((n % 10) + 48);
		n = n / 10;
		ret[char_nbr - 1] = char_c;
		char_nbr--;
	}
	ret[0] = '-';
	ret[char_0] = 0;
	return (ret);
}

char	*ft_itoa(int n, t_data *data)
{
	char	*ret;
	int		char_nbr;
	int		char_0;

	if (n == -2147483648)
		return (ft_strdup("-2147483648", data));
	char_nbr = c_nbr(n);
	char_0 = char_nbr;
	if (n >= 0)
		char_0 = char_0 + 1;
	if (n < 0)
		char_0 = char_0 + 1;
	if (n == 0)
		return (ft_strdup("0", data));
	else
	{
		ret = malloc((char_0) * sizeof(char));
		if (!ret)
			free_all(data, ERR_MAL, 1);
		if (n > 0)
			return (posint(char_nbr, n, ret));
		if (n < 0)
			return (negint(char_nbr, n, ret));
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (fd < 0)
		return ;
	i = 0;
	if (!s)
		return ;
	while (s[i] != 0)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

// char	*ft_strdup(const char *s)
// {
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	ret = malloc((ft_strlen(s) + 1) * sizeof(char));
// 	if (!ret)
// 		return (0);
// 	while (s[i] != 0)
// 	{
// 		ret[i] = s[i];
// 		i++;
// 	}
// 	ret[i] = 0;
// 	return (ret);
// }
