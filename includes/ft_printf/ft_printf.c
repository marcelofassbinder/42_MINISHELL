/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:38:36 by mfassbin          #+#    #+#             */
/*   Updated: 2024/01/20 14:29:48 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(int fd, const char *s, ...)
{
	va_list	args;
	int		count;

	va_start(args, s);
	count = 0;
	while (*s)
	{
		if (*s == '%')
			count += ft_print_format(fd, *(++s), args);
		else
			count += write(fd, s, 1);
		s++;
	}
	va_end (args);
	return (count);
}
/* 
#include <stdio.h>

int main(void)
{
	ft_printf("%x\n", -34);
	printf("%x\n", -34);
} */
