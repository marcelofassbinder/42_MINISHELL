/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:35:20 by mfassbin          #+#    #+#             */
/*   Updated: 2024/01/20 14:28:30 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

int	ft_printf(int fd, const char *s, ...);
int	ft_print_format(int fd, char c, va_list args);
int	ft_putchar(int fd, int c);
int	ft_putstr(int fd, char *s);
int	print_format(int fd, char c, va_list args);
int	ft_putnbr_base(int fd, unsigned long nbr, char *base);
int	ft_putmem(int fd, void *a);
int	ft_putnbr_int(int fd, int nbr, char *base);

#endif