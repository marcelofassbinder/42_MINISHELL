/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:39:19 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/20 14:13:36 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	menos;
	int	nbr;

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
	char	s[] = "2147483647a";
	
	printf("meu atoi: %i\n", ft_atoi(s));
	printf("funcao original: %i\n", atoi(s));
}
 */