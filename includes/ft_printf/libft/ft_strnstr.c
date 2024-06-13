/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcelo <marcelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 12:43:50 by mfassbin          #+#    #+#             */
/*   Updated: 2024/03/27 14:31:49 by marcelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] != '\0' && (big[i + j] == little[j]) && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (0);
}
/* 
#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	printf("ft_strnstr = %s\n", \ 
	ft_strnstr("ola, tudo bem com voce?", "bem", 13));
	printf("strnstr = %s\n", strnstr("ola, tudo bem com voce?", "bem", 13));
} */