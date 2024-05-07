/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:39:10 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/21 17:44:32 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

char	*get_next_line(int fd);
char	*gnl2(int fd, char *test);
char	*next_line(char *test);
char	*refresh(char *test);
char	*ft_strchr_gnl(char *s, size_t c);
char	*ft_strjoin_gnl(char *s1, char *s2, size_t j);
char	*freeall(char *str);
size_t	ft_strlen_gnl(char *str);
size_t	ft_strlcpy_gnl(char *dst, char *src, size_t dstsize);

#endif