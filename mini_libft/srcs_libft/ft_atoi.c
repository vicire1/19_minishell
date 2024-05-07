/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:56:43 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 17:43:24 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static unsigned long long	ft_atoi2(unsigned long long ret, int sign)
{
	if (ret > 9223372036854775807)
	{
		if (sign == 1)
			return (-1);
		if (sign == -1)
			return (0);
	}
	return (ret * sign);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	ret;
	int					sign;

	i = 0;
	ret = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i + 1] == '+' || str[i + 1] == '-')
			return (0);
		if (str[i++] == '-')
			sign = sign * -1;
	}
	while (str[i] >= '0' && str[i] <= '9' && ret < 9223372036854775807)
	{
		ret = (ret * 10) + (str[i] - 48);
		if (!(str[i + 1] >= '0' && str[i + 1] <= '9'))
			return (ft_atoi2(ret, sign));
		i++;
	}
	return (ft_atoi2(ret, sign));
}
