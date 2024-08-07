/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:05:21 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/27 20:46:49 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*d;
	char	*s;
	int		size;

	if (src == NULL)
		return (ft_calloc(sizeof(char), 1));
	s = (char *)src;
	size = ft_strlen(s) + 1;
	d = (char *) ft_calloc(sizeof(char), size);
	if (d == NULL)
		return (NULL);
	ft_strcpy(d, s);
	return (d);
}
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char s[] = "";
	char s2[] = "";

	printf("minha funcao: %s\n", ft_strdup(s));
	printf("funcao original: %s\n", strdup(s2));
} */
