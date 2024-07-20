/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:05:52 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/20 13:18:12 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_is_not_env(t_token *tmp)
{
	if (tmp->type == ENV && tmp->status == IN_S_QUOTE)
		tmp->type = WORD;
 	else if (tmp->type == ENV && ((!tmp->next) || (tmp->next->type != WORD
		&& tmp->next->type != S_QUOTE && tmp->next->type != D_QUOTE)))
		tmp->type = WORD;
}

void	delete_null_nodes(t_token_list *token_list, t_token *tmp)
{
	t_token	*to_free;
	
	delete_node(token_list, tmp->next);
	to_free = tmp;
	tmp = tmp->next;
	delete_node(token_list, to_free);
}

void	delete_expanded_node(t_token_list *token_list, t_token *tmp)
{
	t_token	*to_free;

	tmp->next->type = WORD;
	to_free = tmp;
	tmp = tmp->next;
	delete_node(token_list, to_free);
}

void	delete_env_node(t_token_list *token_list, t_token *tmp)
{
	t_token	*to_free;

	to_free = tmp;
	tmp = tmp->next;
	delete_node(token_list, to_free);	
}

void	check_dollar(t_token_list *token_list, t_shell *shell)
{
	t_token	*tmp;

	tmp = token_list->first;
	while (tmp)
	{
		check_is_not_env(tmp);
		if ((tmp->type == ENV) && tmp->next
			&& (tmp->next->type == WORD || tmp->next->type == ENV))
		{
			tmp->next->data = expand(tmp->next->data, shell);
			if (!tmp->next->data)
			{
				delete_null_nodes(token_list, tmp);
				continue ;
			}
			delete_expanded_node(token_list, tmp);
		}
		else if (tmp->type == ENV && tmp->status == GENERAL && tmp->next &&
			(tmp->next->type == S_QUOTE || tmp->next->type == D_QUOTE))
			delete_env_node(token_list, tmp);
		else
			tmp = tmp->next;
	}
}

char	*expand_digit(char *data)
{
	char	*new_data;
	char	*to_free;
	
	to_free = data;
	if (data[1])
	{
		new_data = ft_substr(data, 1, ft_strlen(data));
		free(to_free);
		return (new_data);
	}
	free (to_free);
	return (ft_strdup(""));
}

char	*expand_minishell(char *data)
{
	char	*ret;
	char	*new_data;
	char	*to_free;

	ret = ft_strdup("minishell");
	to_free = data;
	if (data[1])
	{
		new_data = ft_strjoin(ret, &data[1]);
		to_free = data;
		free(to_free);
		return (new_data);
	}
	free(to_free);
	return (ret);
}

char	*expand_special(char *data)
{
	char	*new_data;

	if (!data[1])
	{
		free (data);
		return (ft_strdup(""));
	}
	else
	{
		new_data = ft_substr(data, 1, ft_strlen(data));
		free (data);
		return (new_data);
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

char	*get_var_value(char *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] && env[i] != '=')
	{
		i++;
		j++;
	}
	if (env[i] != '=')
		return (NULL);
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
		if (!ft_strcmp(cur_env, data))
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

bool	is_special(int c)
{
	char	*specials;

	specials = "~`!@#%^&*()_-+={[\\;|:<,.>/?]}";
	if (ft_strchr(specials, c))
		return (true);
	return (false);
}

char	*expand(char *data, t_shell *shell)
{
	char	*to_expand;
	char	*to_free;
	char	*rest;
	char	*env;
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
	{
		to_free = data;
		env = ft_get_env(data, shell);
		if (env == NULL)
			to_expand = NULL;
		else
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
	specials = "~`!@#$%^&*()-+={[\\;|:<,.>/?]}";
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

int ft_get_pid(t_shell *shell)
{
	int pid;

	//printf("get_pid = %i\n", getpid());
	pid = fork();
	if (pid == 0)
		free_and_exit(shell);
	wait(NULL);
	pid = pid - 1;
	//printf("ft_get_pid = %i\n", pid);
	return(pid);
}
