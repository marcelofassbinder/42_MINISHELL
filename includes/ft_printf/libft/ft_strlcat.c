/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:41:56 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/07 17:48:39 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	size_t			d;
	size_t			s;
	unsigned int	i;
	unsigned int	j;

	d = ft_strlen(dest);
	s = ft_strlen(src);
	i = d;
	j = 0;
	while (src[j] && i + 1 < size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	if (size < d)
		return (size + s);
	return (d + s);
}
/* 
#include <stdio.h>

int	main(void)
{
	char	dest[50] = "ola, ";
	const char	src[] = "tudo bem?";
	unsigned int	i;

	i = 14;

	printf("ft_strlcat = %zu\n", ft_strlcat(dest, src, i));
	printf("novo destino = %s\n", dest);
} */