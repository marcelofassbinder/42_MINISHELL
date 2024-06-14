/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:30:59 by mfassbin          #+#    #+#             */
/*   Updated: 2024/01/20 14:28:30 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_int(int fd, int nbr, char *base)
{
	long	nb;
	int		len;
	int		count;

	nb = (long)nbr;
	len = ft_strlen(base);
	count = 0;
	if (nb < 0)
	{
		write (fd, "-", 1);
		return (ft_putnbr_base(fd, -nb, base) + 1);
	}
	else if (nb < len)
		return (write (fd, &base[nb], 1));
	else
	{
		count = ft_putnbr_base(fd, nb / len, base);
		return (count + ft_putnbr_base(fd, nb % len, base));
	}
}
/* 
#include <stdio.h>

int	main ()
{
	int	a;
	int	c;

	a = -4682;
	c = ft_putnbr_base(a, "0123456789abcdef");
	printf("\n %i\n", c);
	printf("%x\n", a);
} */