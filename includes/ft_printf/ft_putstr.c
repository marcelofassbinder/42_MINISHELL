/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:23:17 by mfassbin          #+#    #+#             */
/*   Updated: 2024/01/20 14:28:30 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(int fd, char *s)
{
	int	count;

	if (!s)
		return (write (fd, "(null)", 6));
	count = 0;
	while (s[count])
	{
		write (fd, &s[count], 1);
		count++;
	}
	return (count);
}
