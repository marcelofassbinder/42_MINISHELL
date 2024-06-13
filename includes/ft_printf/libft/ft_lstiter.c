/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:27:40 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/13 12:54:22 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_iterate(void *ptr)
{
	free(ptr);
	ptr = ft_strdup("42");
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/* #include <stdio.h> 

int main(void)
{
	t_list	*lista;

	lista = ft_lstnew(ft_strdup("67"));
	lista->next = ft_lstnew(ft_strdup("85"));
	lista->next->next = ft_lstnew(ft_strdup("22"));
	printf("%s\n", (char *)lista->content);
	ft_lstiter(lista, &ft_iterate);
	printf("%s\n", (char *)lista->content);
} */