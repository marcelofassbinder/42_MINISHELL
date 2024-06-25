/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:47:09 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/25 12:31:29 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	join_spaces(t_token_list *token_list)
{
	t_token	*tmp;
	t_token	*to_free;

	tmp = token_list->first;
	while (tmp)
	{
		if (tmp->type == W_SPACE && tmp->status == GENERAL)
		{
			while (tmp->next && tmp->next->type == W_SPACE)
			{
				to_free = tmp->next;
				tmp->next = tmp->next->next;
				if (tmp->next)
				{
					tmp->next->prev = tmp;
				}
				free(to_free->data);
				free(to_free);
			}
		}
		tmp = tmp->next;
	}
}

void	delete_node(t_token_list *token_list, t_token *tmp)
{
	if (tmp->prev && tmp->next)
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	else if (tmp->prev)
	{
		tmp->prev->next = NULL;
		token_list->last = tmp->prev;
	}
	else if (tmp->next)
	{
		tmp->next->prev = NULL;
		token_list->first = tmp->next;
	}
	else if (!tmp->next && !tmp->prev)
		token_list->first = NULL;
	free(tmp->data);
	free(tmp);
}

t_token	*join_nodes(t_token_list *token_list, t_token *token)
{
	t_token	*to_delete;

	to_delete = token;
	token = token->next;
	if (token->type == token->prev->type)
	{
		delete_node(token_list, to_delete);
		delete_node(token_list, token);
		return (NULL);
	}
	delete_node(token_list, to_delete);
	while (token)
	{
		if (token->next->status != GENERAL)
		{
			token->data = ft_strjoin(token->data, token->next->data);
			to_delete = token->next;
			delete_node(token_list, to_delete);
		}
		if (!token->next || token->next->status == GENERAL)
			break ;
	}
	token->type = WORD;
	token = token->next;
	return (token);
}

void	join_quotes(t_token_list *token_list)
{
	t_token	*tmp;
	t_token	*to_delete;

	tmp = token_list->first;
	ft_printf(1, "\n----BEFORE JOIN ----\n");
	print_token_list(token_list);
	while (tmp)
	{
		if (tmp->status == GENERAL
			&& (tmp->type == D_QUOTE || tmp->type == S_QUOTE))
		{
			tmp = join_nodes(token_list, tmp);
			if (tmp)
			{
				to_delete = tmp;
				tmp = tmp->next;
				delete_node(token_list, to_delete);
			}
		}
		else
			tmp = tmp->next;
	}
}
