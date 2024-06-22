/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:43:36 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/22 20:23:41 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
/* 
void	join_tokens(t_token_list *token_list)
{
	t_token *tmp;

	tmp = token_list->first;
	while(tmp->next)
	{
		while (tmp->status == IN_S_QUOTE && tmp->next->status == IN_S_QUOTE)
		{
			//FUNCAO QUE JUNTA OS TOKENS E DA FREE;
			
		}
		tmp = tmp->next;
	}
} */

t_token *joined_token(t_token **array, t_token *actual)
{
	int i;

	i = 0;
	while (array[i + 1])
	{
		actual->data = ft_strjoin(actual->data, array[i + 1]->data);
		free(array[i + 1]);
		i++;
	}
	printf("actual token = %s\n", actual->data);
	return(actual);
}

void	join_tokens(t_token **array, t_token_list *token_list)
{
	t_token *tmp;
	t_token *list;

	tmp = *array;
	list = token_list->first;
	while (list)
	{
		if (list == tmp)
		{
			tmp = joined_token(array, tmp);
		}
		list = list->next;
	}
}

int in_same_status(t_token *token)
{
	int same_status;

	same_status = 1;
	while(token->status == token->next->status)
	{
		token = token->next;
		same_status ++;
	}
	return (same_status);
}

t_token	**with_same_status(t_token_list *token_list)
{
	t_token *tmp;
	t_token **array;
	int i;

	ft_printf(1, "entrou na join\n");
	tmp = token_list->first;
	i = 0;
	while (tmp)
	{
		if (tmp->status == IN_S_QUOTE && tmp->next->status == IN_S_QUOTE)
		{
			array = ft_calloc(sizeof(t_token), in_same_status(tmp));
			while (tmp->status == IN_S_QUOTE)
			{
				array[i] = tmp;
				i++;
				tmp = tmp->next;
			}
		}
		else
			tmp = tmp->next;
	}
	i = 0;
	while (array[i])
	{
		ft_printf(1, " array[%i] = %s\n", i, array[i]->data);
		i++;
	}
	return (array);
}
