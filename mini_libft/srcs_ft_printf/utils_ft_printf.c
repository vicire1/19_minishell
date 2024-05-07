/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:36:28 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 17:09:31 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

size_t	ft_strlen_prf(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}

int	ft_putchar_prf(char c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_putstr_prf(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr_prf("(null)"));
	while (str[i] != 0)
	{
		write (1, &str[i], 1);
		i++;
	}
	return (i);
}
