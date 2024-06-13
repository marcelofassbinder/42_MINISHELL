/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:21:25 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/16 20:35:13 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j] != '\0')
		j++;
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (j);
}
/* 
#include <stdio.h>
#include <string.h>
#include <bsd/string.h>

int	main(void)
{
	char	destino[] = "kiwi";
	char	destino2[] = "kiwi";
	char	origem[7] = "banana";
	char	origem2[7] = "banana";
	unsigned int	tam;
	unsigned int	i;
	unsigned int	j;

	tam = 6;
	printf("origem = %s\ndestino = %s\n", origem, destino);
	i = ft_strlcpy(destino, origem, tam);
	printf("destino ft_strlcpy = %s\n", destino);
	printf("retorno = %i\n", i);
	j = strlcpy(destino2, origem2, tam);
	printf("destino strlcpy = %s\n", destino2);
	printf("retorno original = %u\n", j);
}  */
