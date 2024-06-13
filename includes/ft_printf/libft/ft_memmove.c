/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:35:26 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/08 17:20:39 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dtr;
	char	*str;

	dtr = (char *)dest;
	str = (char *)src;
	if (!src && !dest)
		return (dest);
	if (dest < src)
		ft_memcpy(dtr, str, n);
	if (src < dest)
	{
		while (n--)
			dtr[n] = str[n];
	}
	return (dest);
}
/* 
#include <stdio.h>
#include <string.h>

int main(void)
{
    char dest1[] = "banana";
    char dest2[] = "banana";
    char src1[] = "vaca";
    char src2[] = "vaca";
	size_t	n = 2;

	printf("minha funcao: %s\n", (char *)ft_memmove(dest1, src1, n));
	printf("funcao original: %s\n", (char *)memmove(dest2, src2, n));
} */