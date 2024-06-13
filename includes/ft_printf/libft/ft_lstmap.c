/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:10:13 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/19 19:50:52 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* void ft_delete(void *list)
{
	t_list	*a;

	a = (t_list *)list;
	a->content = NULL;
}
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*final;
	void	*content;

	final = NULL;
	while (lst)
	{
		content = f(lst->content);
		temp = ft_lstnew(content);
		if (!temp)
		{
			del(content);
			ft_lstclear(&final, del);
			return (NULL);
		}
		ft_lstadd_back(&final, temp);
		lst = lst->next;
	}
	return (final);
}
