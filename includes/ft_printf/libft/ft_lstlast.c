/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:24:14 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/18 16:18:12 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/* 
#include <stdio.h>

int main(void)
{
	t_list *no;

	no = ft_lstnew("no1");
	no->next = ft_lstnew("no2");
	no->next->next = ft_lstnew("no3");
	no->next->next->next = ft_lstnew("no4");
	printf("o content do ultimo no eh: %s", (char *)ft_lstlast(no)->content);
} */