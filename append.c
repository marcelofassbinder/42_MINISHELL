/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:21:03 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/22 16:52:15 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void append_token(t_token_list *token_list, char *str, enum t_status status, enum t_type type)
{
	t_token *token;
	
	token = ft_calloc(sizeof(t_token), 1);
	if (type == W_SPACE || type == PIPELINE || type == ENV ||
		type == REDIR_IN || type == REDIR_OUT || type == S_QUOTE || type == D_QUOTE)
	{
		token->data = ft_calloc(sizeof(char), 2);
		token->data[0] = *str;
	}
	else
		token->data = str;
	token->status = status;
	token->type = type;
	if (!token_list->first)
	{
		token_list->first = token;
		token_list->last = token;
	}
	else
	{
		token->next = NULL;
		token->prev = token_list->last;	
		token_list->last->next = token;
		token_list->last = token;
	}
}

int append_redir(t_token_list *token_list, char *line, enum t_status status, int i)
{
	char next;

	next = *(line + 1);
	if (*line == REDIRECT_IN)
	{
		if (next != REDIRECT_IN)
			append_token(token_list, line, status, REDIR_IN);
		else if (next == REDIRECT_IN)
		{
			append_token(token_list, "<<", status, HERE_DOC);
			i++;
		}
	}
	else if (*line == REDIRECT_OUT)
	{
		if (next != REDIRECT_OUT)
			append_token(token_list, line, status, REDIR_OUT);
		else if (next == REDIRECT_OUT)	
		{
			append_token(token_list, ">>", status, D_REDIR_OUT);
			i++;
		}
	}
	return (i);
}

int append_word(t_token_list *token_list, char *line, enum t_status status, int i)
{
	char *word;
	int word_len;

	word = line;
	word_len = 0;
	while (is_type_word(*line))
	{
		line++;
		word_len++;
	}
	append_token(token_list, ft_substr(word, 0, word_len), status, WORD);
	return (i + word_len);
}
