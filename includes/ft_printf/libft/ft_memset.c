/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:08:35 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/20 16:20:37 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = (char) c;
		i++;
	}
	return (s);
}
/* 
#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[] = "Marcelo";
	char s2[] = "Marcelo";

    printf("ft_memset: %s\n", (char *)ft_memset(s, 't', 10));
   	printf("memset: %s\n", (char *)memset(s2, 't', 10));
} */