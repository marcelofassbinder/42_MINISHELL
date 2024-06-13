/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:43:58 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/07 17:17:05 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (2048);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	printf("%i\n", ft_isdigit('a'));
	printf("%i\n", isdigit('a'));
}*/