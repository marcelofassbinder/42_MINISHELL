/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:35:20 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/14 22:30:19 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	a;
	long	nb;

	nb = (long)n;
	if (n < 0)
	{
		write((unsigned int)fd, "-", 1);
		nb = nb * (-1);
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	a = nb % 10 + '0';
	write((unsigned int)fd, &a, 1);
}
/* 
int main(void)
{
	ft_putnbr_fd(-2147483648, 1);
} */