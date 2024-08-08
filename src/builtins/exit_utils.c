/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:09:45 by vdecleir          #+#    #+#             */
/*   Updated: 2024/08/08 13:09:46 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	prepare_string_for_comparison(const char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		*sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	return (i);
}

int	compare_with_long_limits(const char *str, int i, int j, int sign)
{
	const char	*cmp_str;
	int			len;

	len = ft_strlen(str + i);
	if (len > 19)
		return (1);
	else if (len < 19)
		return (0);
	if (sign == 1)
		cmp_str = "9223372036854775807";
	else
		cmp_str = "9223372036854775808";
	while (j < 19)
	{
		if (str[i + j] > cmp_str[j])
			return (1);
		else if (str[i + j] < cmp_str[j])
			return (0);
		j++;
	}
	return (0);
}

int	cmd_exit_check_long_overflow(const char *str)
{
	int	sign;
	int	i;

	i = prepare_string_for_comparison(str, &sign);
	return (compare_with_long_limits(str, i, 0, sign));
}

int	cmd_exit_check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+' || ft_isdigit(str[i]))
		i++;
	else
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	if (cmd_exit_check_long_overflow(str))
		return (1);
	return (0);
}

long	cmd_exit_convert(char *str)
{
	long	result;
	int		i;
	int		sign;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
