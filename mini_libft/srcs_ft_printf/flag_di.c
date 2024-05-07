/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:05:55 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 17:10:09 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putnbr_prf(int n)
{
	if (n == -2147483648)
	{
		ft_putstr_prf("-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_putchar_prf('-');
		n = -n ;
	}
	if (n >= 10)
	{
		ft_putnbr_prf(n / 10);
		ft_putnbr_prf(n % 10);
	}
	else
	{
		ft_putchar_prf(n + 48);
	}
	return ;
}
