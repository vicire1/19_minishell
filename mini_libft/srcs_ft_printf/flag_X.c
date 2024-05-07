/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_X.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:50:28 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 17:08:44 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putnbr_hexatoupper(unsigned int n)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (n >= 16)
	{
		ft_putnbr_hexatoupper(n / 16);
		ft_putnbr_hexatoupper(n % 16);
	}
	if (n < 16)
		ft_putchar_prf(base[n]);
}
