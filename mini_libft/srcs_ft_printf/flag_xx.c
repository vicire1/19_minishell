/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_xx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:51:08 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 17:08:47 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putnbr_hexalower(unsigned int n)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
	{
		ft_putnbr_hexalower(n / 16);
		ft_putnbr_hexalower(n % 16);
	}
	else
		ft_putchar_prf(base[n]);
}
