/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:25:38 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/20 14:35:58 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((unsigned char *)&str[i]);
		i++;
	}
	return (0);
}
/* 
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s1[] = "0, 1, 2, 3, 4, 5";    
    char s2[] = "0, 1, 2, 3, 4, 5";    
    int c = '3';
    size_t  n = 15;

    printf("minha funcao: %s\n", (char *)ft_memchr(s1, c, n));     
    printf("funcao original: %s\n", (char *)memchr(s2, c, n));     
} */