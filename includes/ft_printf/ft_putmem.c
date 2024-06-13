/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:44:03 by mfassbin          #+#    #+#             */
/*   Updated: 2024/01/20 14:28:30 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putmem(int fd, void *a)
{
	unsigned long	n;
	int				c;

	if (!a)
		return (write (fd, "(nil)", 5));
	c = 0;
	n = (unsigned long) a;
	c += write(fd, "0x", 2);
	c += ft_putnbr_base(fd, n, "0123456789abcdef");
	return (c);
}
/* #include<stdio.h>

int main()
{
	char *s = "Marcelo";
	
	int c = ft_putmem(s);
	printf("\n%i\n", c);
} */