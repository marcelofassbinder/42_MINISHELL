/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvalues.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:32:27 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/25 20:31:57 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (!shell->envp)
		return (NULL);
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

void	insert_token(char *data, t_token **token)
{
	t_token	*new;
	t_token	*space;

	new = ft_calloc(sizeof(t_token), 1);
	space = ft_calloc(sizeof(t_token), 1);
	new->data = data;
	new->status = GENERAL;
	new->type = WORD;
	space->data = ft_strdup(" ");
	space->status = GENERAL;
	space->type = W_SPACE;
	space->prev = (*token);
	space->next = new;
	new->prev = space;
	new->next = (*token)->next;
	if ((*token)->next)
		(*token)->next->prev = new;
	(*token)->next = space;
}

void	split_env(t_token_list *token_list, t_token **token)
{
	char	**splited;
	int		i;
	t_token	*tmp;

	tmp = (*token);
	splited = ft_split((*token)->next->data, ' ');
	i = 1;
	(*token) = (*token)->next;
	free((*token)->data);
	(*token)->data = splited[0];
	while (splited[i])
	{
		insert_token(splited[i], token);
		(*token) = (*token)->next->next;
		i++;
	}
	(*token) = (*token)->next;
	delete_node(token_list, tmp);
	i = 0;
	free (splited);
}

int ft_get_pid(t_shell *shell)
{
	int pid;

	pid = fork();
	if (pid == 0)
		free_and_exit(shell);
	wait(NULL);
	pid = pid - 1;
	return(pid);
}