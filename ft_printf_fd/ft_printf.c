/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:28:52 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/13 12:50:24 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	conversions(va_list *ap, char c, int fd)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = printf_putchar(va_arg(*ap, int), fd);
	else if (c == 's')
		len = printf_putstr(va_arg(*ap, char *), fd);
	else if (c == '%')
		len = printf_putchar('%', fd);
	else if (c == 'd' || c == 'i')
		len = count_signed(va_arg(*ap, int), fd);
	else if (c == 'u')
		len = count_unsigned(va_arg(*ap, unsigned int), "0123456789", fd);
	else if (c == 'x')
		len = count_unsigned(va_arg(*ap, unsigned int), "0123456789abcdef", fd);
	else if (c == 'X')
		len = count_unsigned(va_arg(*ap, unsigned int), "0123456789ABCDEF", fd);
	else if (c == 'p')
		len = count_adress(va_arg(*ap, void const *), "0123456789abcdef", fd);
	else
		len = printf_putchar(c, fd);
	return (len);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int		i;
	int		count;
	va_list	ap;

	i = 0;
	count = 0;
	if (!format)
		return (0);
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += conversions(&ap, format[i + 1], fd);
			i++;
		}
		else
			count += printf_putchar(format[i], fd);
		i++;
	}
	va_end(ap);
	return (count);
}
