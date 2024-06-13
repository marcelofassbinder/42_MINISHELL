/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:50:29 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/19 14:33:27 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lista;

	if (*lst == NULL)
		*lst = new;
	else
	{
		lista = ft_lstlast(*lst);
		lista->next = new;
	}
}
/* #include <stdio.h>

int main(void)
{
	t_list	*no1;
	t_list	*new;

	no1 = ft_lstnew("inicio");
	new = ft_lstnew("alteracao");
	no1->next = ft_lstnew("meio");
	no1->next->next = ft_lstnew("fim");
	printf("o content do ultimo no eh: %s\n", \
	(char *)ft_lstlast(no1)->content);
	ft_lstadd_back(&no1, new);
	printf("depois da funcao o content do ultimo no eh: %s", \
	(char *)ft_lstlast(no1)->content);
}  */