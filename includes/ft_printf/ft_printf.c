/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:38:36 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/28 19:11:45 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		count;

	va_start(args, s);
	count = 0;
	while (*s)
	{
		if (*s == '%')
			count += ft_print_format(*(++s), args);
		else
			count += write(1, s, 1);
		s++;
	}
	va_end (args);
	return (count);
}
/* 
#include <stdio.h>

int main(void)
{
	ft_printf("%u\n", -34);
	printf("%u\n", -34);
} */
