/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:30:59 by mfassbin          #+#    #+#             */
/*   Updated: 2024/01/20 14:28:30 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(int fd, unsigned long nbr, char *base)
{
	unsigned long		len;
	int					count;

	len = (unsigned long)ft_strlen(base);
	count = 0;
	if (nbr < len)
		return (write (fd, &base[nbr], 1));
	else
	{
		count = ft_putnbr_base(fd, nbr / len, base);
		return (count + ft_putnbr_base(fd, nbr % len, base));
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