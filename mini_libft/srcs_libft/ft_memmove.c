/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:32:14 by lbirloue          #+#    #+#             */
/*   Updated: 2024/05/07 23:59:37 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char		*ret;
	const char	*cpy;

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
