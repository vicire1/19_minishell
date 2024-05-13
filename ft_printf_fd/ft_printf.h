/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:28:58 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/13 12:50:30 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf_fd(int fd, const char *format, ...);
int	printf_putstr(char *str, int fd);
int	count_unsigned(unsigned int nb, char *str, int fd);
int	ft_strlen2(char *str);
int	printf_putchar(int c, int fd);
int	count_signed(int nb, int fd);
int	count_adress(void const *adr, char *str, int fd);

#endif