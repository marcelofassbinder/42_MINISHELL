/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:05:52 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/22 12:44:00 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_expansion(t_token_list *token_list, t_token **tmp, t_shell *shell)
{
	t_token *to_free;

	(*tmp)->next->data = expand((*tmp)->next->data, shell);
	if (!(*tmp)->next->data)
	{
		delete_node(token_list, (*tmp)->next);
		to_free = *tmp;
		*tmp = (*tmp)->next;
		delete_node(token_list, to_free);
	}
	else if (ft_strchr((*tmp)->next->data, ' ') && (*tmp)->next->status == GENERAL)
		split_env(token_list, tmp);
	else
	{
		(*tmp)->next->type = WORD;
		to_free = *tmp;
		*tmp = (*tmp)->next;
		delete_node(token_list, to_free);
	}
}

void check_dollar(t_token_list *token_list, t_shell *shell)
{
	t_token *tmp = token_list->first;
	t_token *to_free;

	while (tmp)
	{
		if (tmp->type == ENV && tmp->status != IN_S_QUOTE && tmp->next &&
			(tmp->next->type == WORD || tmp->next->type == ENV))
		{
			handle_expansion(token_list, &tmp, shell);
			continue;
		}
		if ((tmp->type == ENV && tmp->status == IN_S_QUOTE) || (tmp->type
			== ENV && (!tmp->next || (tmp->next->type != WORD
				&& tmp->next->type != S_QUOTE && tmp->next->type != D_QUOTE))))
			tmp->type = WORD;
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

char	*expand_mode(char *data, t_shell *shell)
{
	char	*new_data;
	char	*number;
	char	*to_free;
	
	to_free = data;
	if (data[0] == '?' || data[0] == '$')
	{
		if (data[0] == '?')
			number = ft_itoa(shell->exit_status);
		else
			number = ft_itoa(shell->pid);
		new_data = ft_strjoin(number, &data[1]);
		free(to_free);
		return (new_data);
	}
	else if (data[0] == '0')
		return (expand_minishell(data));
	else if (ft_isdigit (data[0]))
		return (expand_digit(data));
	else
		return (expand_special(data));
}

char	*expand_normal(char *data, t_shell *shell)
{
	char	*env;
	char	*expanded;
	char	*to_free;
	
	to_free = data;
	env = ft_get_env(data, shell);
	if (!env)
	{
		free(to_free);
		return (NULL);	
	}
	expanded = ft_strdup(env);
	free(env);
	free(to_free);
	return (expanded);
}

char	*expand(char *data, t_shell *shell)
{
	char	*to_expand;
	char	*rest;
	int		i;

	if (data[0] == '?' || data[0] == '$' || ft_isdigit(data[0])
		|| is_special(data[0]))
		return (expand_mode(data, shell));
	else if (find_special(data))
	{
		i = count_special(data, find_special(data));
		to_expand = ft_substr(data, 0, i);
		rest = ft_substr(data, i, ft_strlen(data) - i);
	}
	else
		return (expand_normal(data, shell));
	return (expand_aux(data, to_expand, rest, shell));
}
