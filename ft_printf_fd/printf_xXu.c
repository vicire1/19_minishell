/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_xXu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:00:30 by vdecleir          #+#    #+#             */
/*   Updated: 2024/02/28 14:02:38 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_base(unsigned int nb, char *str, int fd)
{
	unsigned int	base;

	base = ft_strlen2(str);
	if (nb < 0)
	{
		printf_putchar('-', fd);
		nb = -nb;
	}
	if (nb >= base)
	{
		ft_putnbr_base(nb / base, str, fd);
		ft_putnbr_base(nb % base, str, fd);
	}
	if (nb < base)
	{
		printf_putchar(str[nb], fd);
	}
}

int	count_unsigned(unsigned int nb, char *str, int fd)
{
	int	len;
	int	base;

	len = 0;
	base = ft_strlen2(str);
	ft_putnbr_base(nb, str, fd);
	if (!str)
		return (0);
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / base;
		len++;
	}
	return (len);
}
