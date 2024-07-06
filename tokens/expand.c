/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:05:52 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/06 14:49:18 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_dollar(t_token_list *token_list, t_shell *shell)
{
	t_token	*tmp;
	t_token	*to_free;

	tmp = token_list->first;
	while (tmp)
	{
		if (tmp->type == ENV && tmp->status != IN_S_QUOTE && tmp->next
			&& tmp->next->type == WORD)
		{
			tmp->next->data = expand(tmp->next->data, shell);
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
char	*expand_status(char *data, t_shell *shell)
{
	char	*new_data;
	char	*number;
	char	*to_free;

	to_free = data;
	number = ft_itoa(shell->exit_status);
	new_data = ft_strjoin(number, &data[1]);
	free(to_free);
	return (new_data);
}

char	*get_var_value(char *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != '=')
	{
		i++;
		j++;
	}
	i++;
	while (env[j])
		j++;
	return (ft_substr(env, i, j));
}

char	*ft_get_env(char *data, t_shell *shell)
{
	int		i;
	char	*cur_env;

	i = 0;
	while (shell->envp[i])
	{
		cur_env = get_variable_name(shell->envp[i]);
		if (!ft_strncmp(cur_env, data, ft_strlen(data + 1)))
		{
			free(cur_env);
			return (get_var_value(shell->envp[i]));
		}
		i++;
		free(cur_env);
	}
	return (NULL);
}

char	*expand_aux(char *data, char *to_expand, char *rest, t_shell *shell)
{
	char	*new;
	char	*to_free;
	
	to_free = ft_strdup(ft_get_env(to_expand, shell));
	new = ft_strjoin(to_free, rest);
	free_strings(data, to_expand, rest);
	return (new);
}

char	*expand(char *data, t_shell *shell)
{
	char	*to_expand;
	char	*to_free;
	char	*rest;
	char	*env;
	int		i;

	if (data[0] == '?')
		return (expand_status(data, shell));
	if (find_special(data))
	{
		i = count_special(data, find_special(data));
		to_expand = ft_substr(data, 0, i);
		rest = ft_substr(data, i, ft_strlen(data) - i);
	}
	else
	{
		to_free = data;
		env = ft_get_env(data, shell);
		to_expand = ft_strdup(env);
		free(env);
		free(to_free);
		return (to_expand);
	}
	return (expand_aux(data, to_expand, rest, shell));
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
