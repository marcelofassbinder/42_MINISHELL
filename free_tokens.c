/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:14:35 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/02 20:05:48 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_token_list(t_token_list *token_list)
{
	t_token	*tmp;
	t_token	*to_free;

	tmp = token_list->first;
	while (tmp)
	{
		to_free = tmp;
		tmp = tmp->next;
		free(to_free->data);
		free(to_free);
	}
}

void	free_env(t_token *token)
{
	t_token *to_free;

	to_free = token;
	free(to_free->data);
	free(to_free);
}

void	exit_line(t_shell *shell)
{
	free(shell->line);
	free(shell);
	ft_printf(STDOUT_FILENO, "exit\n");
	exit(0);
}

void	free_strings(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
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
