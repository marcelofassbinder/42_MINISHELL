/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:25:56 by marcelo           #+#    #+#             */
/*   Updated: 2024/07/27 20:45:55 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
/* 
#include <stdio.h>

int main(void)
{
	int i;

	i = ft_strcmp("echo", "echo");
	printf("iguais = %i\n", i);
	i = ft_strcmp("echo", "ech");
	printf("echo e ech = %i\n", i);
	i = ft_strcmp("echo", "echoo");
	printf("echo e echoo = %i\n", i);
} */