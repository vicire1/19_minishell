/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:36:35 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 17:42:56 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	verif(const char *s1, const char *s2, size_t n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s2[j] != '\0' )
	{
		if (s2[j] != s1[n + j])
			i = 1;
		j++;
	}
	return (i);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == 0)
		return ((char *)haystack);
	else if (haystack[0] == 0 || 1 > len || (haystack[0] == 0
			&& (needle[0] != 0)))
		return (NULL);
	while (haystack[i] != 0)
		i++;
	j = 0;
	while (j < i - 1 && j < len - 1)
	{
		if (j + ft_strlen(needle) <= len && needle[0] == haystack[j])
		{
			if (verif(haystack, needle, j) == 0)
				return ((char *)haystack + j);
		}
		j++;
	}
	if (ft_strlen(needle) == 1 && needle[0] == haystack[0])
		return ((char *) haystack);
	return (NULL);
}
