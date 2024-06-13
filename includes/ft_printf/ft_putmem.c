/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:44:03 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/28 19:19:12 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putmem(void *a)
{
	unsigned long	n;
	int				c;

	if (!a)
		return (write (1, "(nil)", 5));
	c = 0;
	n = (unsigned long) a;
	c += write(1, "0x", 2);
	c += ft_putnbr_base(n, "0123456789abcdef");
	return (c);
}
/* #include<stdio.h>

int main()
{
	char *s = "Marcelo";
	
	int c = ft_putmem(s);
	printf("\n%i\n", c);
} */