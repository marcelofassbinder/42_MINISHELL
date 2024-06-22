/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:05:52 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/22 17:19:48 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void expand(t_token_list *token_list)
{
	t_token *tmp;
	t_token *to_free;
	
	tmp = token_list->first;
	while(tmp->next)
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

int		count_special(char *data, char special)
{
	int	i;

	i = 0;
	while (data[i] != special && data[i])
		i++;
	return (i);
}

void	free_strings(char *s1, char *s2, char *s3, char *s4)
{
	free(s1);
	free(s2);
	free(s3);
	free(s4);
}

char	*check_quotes(char *data)
{
	char	*to_expand;
	char	*to_free;
	char	*rest;
	char	*new;
	int		i;

	if (find_special(data))
		i = count_special(data, find_special(data));
		else if (ft_strchr(data, S_QUOTE))
			i = count_special(data, S_QUOTE);
		else if (ft_strchr(data, D_QUOTE))
			i = count_special(data, D_QUOTE);
	else
	{
		printf("entrou\n");
		printf("DATA = %s\n", data);
		to_free = data;
		to_expand = ft_strdup(getenv(data));
		free(to_free);
		return(to_expand);
	}
	to_expand = ft_substr(data, 0, i);
	rest = ft_substr(data, i, ft_strlen(data) - i);
	to_free = ft_strdup(getenv(to_expand));
	printf("REST = %s\n TO_EXPAND = %s\n", rest, to_expand);
	new = ft_strjoin(to_free, rest);
	free_strings(to_expand, to_free, rest, data);
	return(new);
}
