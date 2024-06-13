/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:58:49 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/19 17:04:29 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* 
void ft_delete(void *list)
{
	list = NULL;
} */

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*next;

	ptr = *lst;
	while (ptr)
	{
		next = ptr->next;
		del(ptr->content);
		free(ptr);
		ptr = next;
	}
	*lst = NULL;
}
/* 
#include <stdio.h>

int main(void)
{
	t_list	*list;

	list = ft_lstnew("primeiro no");
	list->next = ft_lstnew("segundo no");
	list->next->next = ft_lstnew("terceiro no");
	printf("%s\n", (char *)list->content);
	ft_lstclear(&list, ft_delete);
	printf("%s\n", (char *)list);
} */