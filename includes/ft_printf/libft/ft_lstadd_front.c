/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:24:58 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/18 15:03:58 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/* 
#include <stdio.h>

int main(void)
{
	t_list *lista;
	t_list *lista2;
	lista = malloc(sizeof(t_list));
	lista2 = malloc(sizeof(t_list));
	lista->content = "marcelo";
	lista->next = lista2;
	lista2->content = "gremio";
	lista2->next = NULL;
	t_list *new;
	new = malloc(sizeof(t_list));
	new->content = "abcd";
	new->next = NULL;
	printf("%s\n", (char *)new->next);
	ft_lstadd_front(&lista, new);
	printf("%s\n", (char *)new->next);
} */ 