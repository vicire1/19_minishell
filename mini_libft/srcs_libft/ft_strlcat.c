/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:16:18 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 16:41:31 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*dest;
	const char	*source;
	size_t		n;
	size_t		dst_size;

	dest = dst;
	n = dstsize;
	source = src;
	while (n-- != 0 && *dest)
		dest++;
	dst_size = dest - dst;
	n = dstsize - dst_size;
	if (n == 0)
		return (ft_strlen(source) + dst_size);
	while (*source)
	{
		if (n != 1)
		{
			*dest++ = *source;
			n--;
		}
		source++;
	}
	*dest = '\0';
	return ((source - src) + dst_size);
}
