/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:39:19 by mfassbin          #+#    #+#             */
/*   Updated: 2023/12/12 21:09:48 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoi(const char *str)
{
	long long	i;
	long long	menos;
	long long	nbr;

	nbr = 0;
	menos = 0;
	i = 0;
	while (str[i] != '\0' && ((str[i] <= 13 && str[i] >= 9) || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			menos++;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (menos == 0)
		return (nbr);
	return (-nbr);
}
/* #include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	s[] = "123456789625231";
	
	printf("meu atoi: %lli\n", ft_atoi(s));
	printf("funcao original: %i\n", atoi(s));
}
 */