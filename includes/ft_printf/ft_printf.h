/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:35:20 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/28 19:19:27 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

int	ft_printf(const char *s, ...);
int	ft_print_format(char c, va_list args);
int	ft_putchar(int c);
int	ft_putstr(char *s);
int	print_format(char c, va_list args);
int	ft_putnbr_base(unsigned long nbr, char *base);
int	ft_putmem(void *a);
int	ft_putnbr_int(int nbr, char *base);

#endif