/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:29:54 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/19 15:57:45 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* 
void ft_delete(void *list)
{
	t_list	*a;

	a = (t_list *)list;
	a->content = NULL;
} */

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}
/* 
#include<stdio.h>

int main(void)
{
	t_list *list;

	list = ft_lstnew("conteudo que vai ser apagado");
	printf("%s\n", (char *)list->content);
	ft_lstdelone(list, ft_delete);
	printf("%s\n", (char *)list->content);
} */