/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:32:14 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 16:40:31 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t		i;
	char		*ret;
	const char	*cpy;

	i = 0;
	ret = (char *)dest;
	cpy = (const char *)src;
	if (len == 0)
		return (dest);
	if (dest > src)
	{
		while (len - 1 > 0)
		{
			ret[len -1] = cpy[len - 1];
			len--;
		}
		ret[len - 1] = cpy[len - 1];
	}
	else
		ft_memcpy(dest, src, len);
	return ((void *)dest);
}
