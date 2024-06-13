/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:50:09 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/07 17:15:30 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c < 0 || c > 127)
		return (0);
	return (1);
}

/* #include <stdio.h>
#include <ctype.h>

int main(void)
{
    printf("%i\n", ft_isascii(-1));
    printf("%i\n", isascii(-1));
} */