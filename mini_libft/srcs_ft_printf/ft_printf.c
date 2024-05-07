/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:04:34 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 17:07:42 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printf2(const char *str, va_list lst)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '%')
			{
				j += ft_putchar_prf('%');
				i++;
			}
			else if (ft_verif_flag(str[i + 1]) == 0)
			{
				j += repartflag(str[i + 1], lst);
				i++;
			}
		}
		else if (str[i] != 0)
			j += ft_putchar_prf(str[i]);
		i++;
	}
	return (j);
}

int	ft_printf(const char *str, ...)
{
	va_list	lst;
	int		i;

	if (!str)
		return (-1);
	va_start(lst, str);
	i = ft_printf2(str, lst);
	va_end(lst);
	return (i);
}
