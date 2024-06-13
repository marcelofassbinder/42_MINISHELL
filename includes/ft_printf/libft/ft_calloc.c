/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:27:54 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/10 16:42:15 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)malloc (size * nmemb);
	if (str == 0)
		return (0);
	i = 0;
	while (i < nmemb * size)
	{
		str[i] = 0;
		i++;
	}
	return ((void *)str);
}
/* 
#include <stdio.h>

int	main(void)
{
	printf("minha funcao: %zu\n", (size_t) ft_calloc(0, 0));
	printf("funcao original: %zu\n", (size_t) calloc(0, 0));	
} */