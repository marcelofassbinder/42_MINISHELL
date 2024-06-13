/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:53:38 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/18 15:21:49 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/* 
#include<stdio.h>

int main(void)
{
	t_list	*no1;
	t_list	*no2;
	t_list	*no3;
	t_list	*no4;

	no1 = malloc(sizeof(t_list));
	no2 = malloc(sizeof(t_list));
	no3 = malloc(sizeof(t_list));
	no4 = malloc(sizeof(t_list));
	no1->next = no2;
	no2->next = no3;
	ft_lstadd_front(&no1, no4);
	printf("%i", ft_lstsize(no1));
} */
