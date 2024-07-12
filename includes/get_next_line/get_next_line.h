/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:59:14 by mfassbin          #+#    #+#             */
/*   Updated: 2024/01/06 21:26:16 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
int		nextline(char *s);
char	*read_line(int fd, char *str);
char	*ft_strjoin2(char *s1, char *s2);
size_t	ft_strlen2(char *str);
size_t	ft_strlcpy2(char *dest, char *src, size_t size);
char	*ft_strrchr2(char *s, int c);

#endif