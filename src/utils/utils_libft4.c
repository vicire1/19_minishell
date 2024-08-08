/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:04:49 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/08 13:08:03 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
