/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:45:27 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/07 17:14:49 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
		return (0);
	return (1024);
}
/* 
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("%i\n", ft_isalpha('a'));
	printf("%i\n", isalpha('a'));
} */