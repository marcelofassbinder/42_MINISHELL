/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:02:47 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/14 22:45:01 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	while (*s)
	{
		write((unsigned int)fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}

/* 
int main(void)
{
	ft_putendl_fd("marcelo", 1);
} */