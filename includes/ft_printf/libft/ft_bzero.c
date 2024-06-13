/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:46:27 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/20 14:13:26 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
/* 
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[]= "Marcelo";
    char s2[]= "Marcelo";
    char *ptr = &s[4];
    char *ptr2 = &s2[4];

// teste minha funcao
    printf("antes (ft_bzero): %s\n", s);
    ft_bzero(ptr, 1);
    printf("depois(ft_bzero): %s\n", s);
//teste funcao original
    printf("antes (bzero): %s\n", s2);
    bzero(ptr2, 1);
    printf("depois(bzero): %s\n", s2);
} */