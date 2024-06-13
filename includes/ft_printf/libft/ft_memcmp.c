/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:42:42 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/10 15:41:37 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] > str2[i])
			return (1);
		if (str1[i] < str2[i])
			return (-1);
		i++;
	}
	return (0);
}
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str1[] = "marcelo";
	char str2[] = "martelo";
	size_t n = 4;

	printf("ft_memcmp = %i\n", ft_memcmp(str1, str2, n));
	printf("funcao original = %i\n", memcmp(str1, str2, n));
} */