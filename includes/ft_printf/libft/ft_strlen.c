/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:16:28 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/07 16:21:18 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("%lu\n", ft_strlen("marcelo e dois caes"));
	printf("%lu\n", strlen("marcelo e dois caes"));
} */
