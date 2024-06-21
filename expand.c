/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:05:52 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/21 22:12:09 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void expand(t_token_list *token_list)
{
	t_token *tmp;
	t_token *to_free;
	
	tmp = token_list->first;
	while(tmp)
	{
		if (tmp->type == ENV && tmp->status != IN_S_QUOTE && tmp->next->type == WORD)
		{
			tmp->next->data = check_quotes(tmp->next->data);
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			to_free = tmp;
			tmp = tmp->next;
			free(to_free->data);
			free(to_free);
		}
		else
			tmp = tmp->next;
	}
	ft_printf(1, "\n----EXPANDED ----\n");
	print_token_list(token_list);;
}

char *check_quotes(char *data)
{
	char *to_expand = NULL;
	char *to_free;
	char *rest;
	char *new;
	int i;

	if (ft_strchr(data, S_QUOTE))
	{	
		i = 0;
		ft_printf(1, "data = %s\n", data);
		while (data[i] != S_QUOTE && data[i])
			i++;
		to_expand = ft_substr(data, 0, i);
		rest = ft_substr(data, i, ft_strlen(data) - i);
		ft_printf(1, "rest = %s\n", rest);
	}
	else if (ft_strchr(data, D_QUOTE))
	{	
		i = 0;
		ft_printf(1, "data = %s\n", data);
		while (data[i] != D_QUOTE && data[i])
			i++;
		to_expand = ft_substr(data, 0, i);
		rest = ft_substr(data, i, ft_strlen(data) - i);
	}
	else
	{
		to_free = data;
		to_expand = ft_strdup(getenv(data));
		free(to_free);
		return(to_expand);
	}
	new = ft_strjoin(ft_strdup(getenv(data)), rest);
	free(to_expand);
	free(rest);
	free(data);
	ft_printf(1, "\nnew = %s\n", new);
	return(new);
}
