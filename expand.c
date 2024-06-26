/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:05:52 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/25 14:46:24 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_dollar(t_token_list *token_list)
{
	t_token	*tmp;
	t_token	*to_free;

	tmp = token_list->first;
	while (tmp)
	{
		if (tmp->type == ENV && tmp->status != IN_S_QUOTE && tmp->next
			&& tmp->next->type == WORD)
		{
			tmp->next->data = expand(tmp->next->data);
			to_free = tmp;
			tmp = tmp->next;
			delete_node(token_list, to_free);
		}
		else if (tmp->type == ENV && tmp->status == GENERAL && tmp->next &&
			(tmp->next->type == S_QUOTE || tmp->next->type == D_QUOTE))
		{
			to_free = tmp;
			tmp = tmp->next;
			delete_node(token_list, to_free);
		}
		else
			tmp = tmp->next;
	}
}

char	*expand(char *data)
{
	char	*to_expand;
	char	*to_free;
	char	*rest;
	char	*new;
	int		i;

	if (find_special(data))
	{
		i = count_special(data, find_special(data));
		to_expand = ft_substr(data, 0, i);
		rest = ft_substr(data, i, ft_strlen(data) - i);
	}
	else
	{
		to_free = data;
		to_expand = ft_strdup(getenv(data));
		free(to_free);
		return (to_expand);
	}
	to_free = ft_strdup(getenv(to_expand));
	new = ft_strjoin(to_free, rest);
	free_strings(to_expand, rest, data);
	return (new);
}

char	find_special(char *data)
{
	char	*specials;
	int		i;
	int		j;

	i = 0;
	specials = "~`!@#$%^&*()_-+={[\\;|:<,.>/?]}";
	while (data[i])
	{
		j = 0;
		while (specials[j])
		{
			if (data[i] == specials[j])
				return (data[i]);
			j++;
		}
		i++;
	}
	return (0);
}

int	count_special(char *data, char special)
{
	int	i;

	i = 0;
	while (data[i] != special && data[i])
		i++;
	return (i);
}
