/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:44:25 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/28 19:20:28 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_format(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg(args, int));
	if (c == 's')
		count += ft_putstr(va_arg(args, char *));
	if (c == 'd' || c == 'i')
		count += ft_putnbr_int(va_arg(args, int), "0123456789");
	if (c == 'x')
		count += ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef");
	if (c == 'X')
		count += ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF");
	if (c == 'p')
		count += ft_putmem(va_arg(args, void *));
	if (c == 'u')
		count += ft_putnbr_base(va_arg(args, unsigned int), "0123456789");
	if (c == '%')
		count += ft_putchar('%');
	return (count);
}
