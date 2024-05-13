/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:37:50 by vdecleir          #+#    #+#             */
/*   Updated: 2024/02/28 14:03:20 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_adress(unsigned long int adress, char *str, int fd)
{
	unsigned long int	base;

	base = ft_strlen2(str);
	if (adress < 0)
	{
		printf_putchar('-', fd);
		adress = -adress;
	}
	if (adress >= base)
	{
		print_adress(adress / base, str, fd);
		print_adress(adress % base, str, fd);
	}
	if (adress < base)
		printf_putchar(str[adress], fd);
}

int	count_adress(void const *adr, char *str, int fd)
{
	unsigned long int	adress;
	int					count;
	int					base;

	if (!str)
		return (0);
	adress = (unsigned long int)adr;
	base = ft_strlen2(str);
	printf_putstr("0x", fd);
	count = 2;
	print_adress(adress, str, fd);
	if (adress == 0)
		return (3);
	while (adress > 0)
	{
		adress = adress / base;
		count++;
	}
	return (count);
}
