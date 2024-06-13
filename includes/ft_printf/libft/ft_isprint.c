/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:30:41 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/07 17:17:54 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c < 32 || c > 126)
		return (0);
	return (16384);
}

/* #include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("%i\n", ft_isprint(0));
	printf("%i\n", isprint(0));
} */
