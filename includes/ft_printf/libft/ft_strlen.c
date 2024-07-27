/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:16:28 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/27 13:40:50 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
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
