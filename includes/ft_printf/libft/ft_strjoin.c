/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:23:11 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/30 20:15:46 by vinivaccari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*check_str_null(char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
	{
		free(s1);
		return (ft_strdup(s2));
	}
	return (s1);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;
	int		size;

	if (!s1 || !s2)
		return (check_str_null(s1, s2));
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *) ft_calloc(sizeof(char), size);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	free(s1);
	result[i] = '\0';
	return (result);
}
/* 
#include <stdio.h>

int	main(void)
{
	char 	s1[] = "Gremio ";
	char	s2[] = "campeao mundial";	

	printf("%s", ft_strjoin(s1, s2));
} */
