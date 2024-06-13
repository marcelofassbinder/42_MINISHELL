/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:07:29 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/07 17:13:35 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c < 'A' || (c > 'Z' && c < 'a') || c > 'z') && (c < 48 || c > 57))
		return (0);
	return (8);
}
/* 
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    printf("%i\n", ft_isalnum('r'));
    printf("%i\n", isalnum('r'));
} */