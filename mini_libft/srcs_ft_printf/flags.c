/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:05:49 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 17:09:23 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	repartflag(const char c, va_list lst)
{
	int	count;

	count = 0;
	if (c == 'd' || c == 'i')
		count = nbr_count(va_arg(lst, int));
	else if (c == 'x')
		count = nbr_hexa(va_arg(lst, int), 0);
	else if (c == 'X')
		count = nbr_hexa(va_arg(lst, int), 1);
	else if (c == 'c')
		count = ft_putchar_prf(va_arg(lst, int));
	else if (c == 's')
		count = ft_putstr_prf(va_arg(lst, char *));
	else if (c == 'u')
		count = nbr_count_unsigned(va_arg(lst, unsigned int));
	else if (c == 'p')
		count = nbr_count_p(va_arg(lst, void const *));
	return (count);
}

int	ft_verif_flag(const char c)
{
	if (c == 'd' || c == 'i' || c == 'x' || c == 'X' || c == 'c'
		|| c == 's' || c == 'u' || c == 'p')
		return (0);
	return (-1);
}
