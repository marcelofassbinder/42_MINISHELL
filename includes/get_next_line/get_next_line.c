/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:58:39 by mfassbin          #+#    #+#             */
/*   Updated: 2024/01/07 14:41:59 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *dest)
{
	char	*buf;
	int		count_read;

	count_read = 1;
	while (nextline(dest) == 0 && count_read != 0)
	{
		buf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		count_read = read(fd, buf, BUFFER_SIZE);
		if (count_read == 0)
		{
			free(buf);
			return (dest);
		}
		if (count_read == -1)
		{
			free(buf);
			free(dest);
			return (NULL);
		}
		dest = ft_strjoin2(dest, buf);
		free(buf);
	}
	return (dest);
}

char	*clean_line(char *dest)
{
	char	*line;
	int		next;

	next = nextline(dest);
	if (next == 0)
		next = ft_strlen2(dest);
	if (next == 0)
		return (NULL);
	line = ft_calloc(sizeof(char), (next + 1));
	if (!line)
	{
		free (dest);
		return (NULL);
	}
	ft_strlcpy2(line, dest, next + 1);
	return (line);
}

char	*new_dest(char *dest)
{
	char	*new_dest;
	int		i;
	int		len;

	len = ft_strlen2(dest);
	i = nextline(dest);
	if (i == 0 || len == 0)
	{
		free (dest);
		return (NULL);
	}
	new_dest = ft_calloc(sizeof(char), len - i + 1);
	if (!new_dest)
	{
		free(dest);
		return (NULL);
	}
	ft_strlcpy2(new_dest, &dest[i], len - i + 1); 
	free(dest);
	return (new_dest);
}

char	*get_next_line(int fd)
{
	static char		*dest; 
	char			*line;

	if (fd == -1)
		free(dest);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	dest = read_line(fd, dest);
	if (!dest)
		return (NULL);
	line = clean_line(dest);
	dest = new_dest(dest);
	return (line);
}
/*  #include <stdio.h>
#include <fcntl.h>

int main()
{
	char *a;
	int i = 0;
	int fd = open("read_error.txt", O_RDONLY);
	
	while (a)
	{
		a = get_next_line(fd);
		printf(" %i -> %s", i, a);
		free(a);
		i++;
	}
}  */