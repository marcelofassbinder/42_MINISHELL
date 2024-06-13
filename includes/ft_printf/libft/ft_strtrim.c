/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:39:04 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/20 16:22:01 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	result = NULL;
	if (s1 && set)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && start < end && ft_strchr(set, s1[start]) != NULL)
			start++;
		while (s1[end -1] && start < end && ft_strchr(set, s1[end - 1]) != NULL)
			end--;
		result = ft_substr(s1, start, end - start);
	}
	return (result);
}
/* 
#include<stdio.h>

int	main(void)
{
	printf("%s\n", ft_strtrim("  \t \t \n   \n\n\n\t", " \n\t"));
} */