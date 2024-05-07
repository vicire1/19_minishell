/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:56:13 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 17:08:07 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	nbr_hexa(unsigned int n, int i)
{
	unsigned long	tempo;
	int				count;

	count = 0;
	tempo = n;
	if (i == 0)
		ft_putnbr_hexalower(n);
	if (i == 1)
		ft_putnbr_hexatoupper(n);
	if (n == 0)
		return (1);
	while (tempo > 0)
	{
		tempo = tempo / 16;
		count++;
	}
	return (count);
}

int	nbr_count(int n)
{
	int	count;
	int	tempo;

	count = 0;
	tempo = n;
	ft_putnbr_prf(n);
	if (n < 0)
	{
		count++;
		tempo = tempo * -1;
	}
	if (n == 0)
		return (1);
	if (n == INT_MIN)
		return (11);
	while (tempo > 0)
	{
		count++;
		tempo = tempo / 10;
	}
	return (count);
}

int	nbr_count_unsigned(unsigned int n)
{
	unsigned int	tempo;
	int				count;

	count = 0;
	tempo = n;
	ft_putnbr_unsigned(n);
	if (n == 0)
		return (1);
	while (tempo > 0)
	{
		count++;
		tempo = tempo / 10;
	}
	return (count);
}

int	nbr_count_p(void const *p)
{
	int				count;
	unsigned long	n;
	unsigned long	tempo;

	count = 0;
	n = (unsigned long)p;
	count = 0;
	tempo = n;
	if (tempo > 0)
	{
		while (tempo > 0)
		{
			tempo = tempo / 16;
			count++;
		}
	}
	else if (tempo == 0)
		count = 1;
	count += ft_putstr_prf("0x");
	ft_putnbr_adress(n);
	return (count);
}
