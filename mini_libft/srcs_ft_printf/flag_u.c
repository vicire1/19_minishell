/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:07:49 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 17:08:40 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putnbr_unsigned(unsigned int n)
{
	if (n >= 10)
	{
		ft_putnbr_prf(n / 10);
		ft_putnbr_prf(n % 10);
	}
	else
	{
		ft_putchar_prf(n + 48);
	}
}
