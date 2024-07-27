/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:13:59 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/26 16:29:41 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*get_next_redir(t_token *token)
{
	if (token->next)
		token = token->next;
	else 
		return (NULL);
	while (token && !is_redir(token) && token->type != PIPELINE)
		token = token->next;
	if (token && token->type == PIPELINE)
		return (NULL);
	return(token);
}

bool	last_redir(t_token *token)
{
	if (token->type != REDIR_IN && token->type != REDIR_OUT && token->type != D_REDIR_OUT && token->type != HERE_DOC)
		return (false);
	token = get_next_redir(token);
	if (!token)
		return (true);
	return (false);
}

t_token	*find_last_or_pipe(t_token *token, int flag)
{
	while (token && token->next)
	{
		if (token->type == PIPELINE && token->status == GENERAL)
			return (token);
		token = token->next;
	}
	if (flag == 1)
		return (token);
	return (NULL);
}

t_token	*get_previous_redir(t_token *token)
{
	if (token && token->prev)
	{
		token = token->prev;
		while (token && token->type != PIPELINE)
		{
			if (is_redir(token))
				return (token);
			token = token->prev;
		}
	}
	/* else if (is_redir(token) && !token->prev)
		return (token); */
	else	
		return (NULL);
	return (NULL);
}