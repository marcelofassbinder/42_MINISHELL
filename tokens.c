/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:48:24 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/21 15:41:27 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	tokenizer(char *line)
{
	t_token_list *token_list;
	enum t_status 	status;
	enum t_type 	word_len;
	int 	i;
	char 	*word;

	token_list = ft_calloc(sizeof(t_token_list), 1);
	i = 0;
	status = GENERAL;
	while(*line)
	{
		if (is_type_word(*line, status))
		{
			word = line;
			word_len = 0;
			while (is_type_word(*line, status))
			{
				line++;
				word_len++;
			}
			token_list = append_str_token(token_list, ft_substr(word, 0, word_len), status, WORD);
		}	
		status = change_status(*line, status);
		if (ft_isspace(*line))
			token_list = append_char_token(token_list, *line, status, W_SPACE);
		if (*line == PIPE)
			token_list = append_char_token(token_list, *line, status, PIPELINE);
		if (*line == DOLLAR)
			token_list = append_char_token(token_list, *line, status, ENV);
		if (*line == REDIRECT_IN)
		{
			if (*(line + 1) != REDIRECT_IN)
				token_list = append_char_token(token_list, *line, status, REDIR_IN);
			else if (*(line + 1) == REDIRECT_IN)
			{
				token_list = append_str_token(token_list, "<<", status, HERE_DOC);
				line ++;
			}
		}
		if (*line == REDIRECT_OUT)
		{
			if (*(line + 1) != REDIRECT_OUT)
				token_list = append_char_token(token_list, *line, status, REDIR_OUT);
			else if (*(line + 1) == REDIRECT_OUT)	
			{
				token_list = append_str_token(token_list, ">>", status, D_REDIR_OUT);
				line ++;
			}
		}
		line++;
	}
	print_token_list(token_list);

}

t_token_list *append_str_token(t_token_list *token_list, char *str, enum t_status status, enum t_type type)
{
	t_token *token;
	
	token = ft_calloc(sizeof(t_token), 1);
	token->data = str;
	token->status = status;
	token->type = type;
	if (!token_list->first)
	{
		token->prev = NULL;
		token->next = NULL;
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
	return (token_list);
}

t_token_list *append_char_token(t_token_list *token_list, char c, enum t_status status, enum t_type type)
{
	t_token *token;
	char *data;
	
	token = ft_calloc(sizeof(t_token), 1);
	data = ft_calloc(sizeof(char), 2);
	data[0] = c;
	token->data = data;
	token->status = status;
	token->type = type;
	if (!token_list->first)
	{
		token->prev = NULL;
		token->next = NULL;
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
	return (token_list);
}

void print_token_list(t_token_list *token_list)
{
	int i;
	t_token *ptr;
	char *s[] = {"GENERAL", "IN_S_QUOTE", "IN_D_QUOTE", "W_SPACE", "WORD", "PIPELINE", "ENV", "REDIR_IN", "REDIR_OUT", "D_REDIR_OUT", "HERE_DOC"};

	ptr = token_list->first;
	i = 1;
	printf("| %-3s | %-20s | %-3s | %-15s | %-15s |\n", "ID", "TOKEN", "LEN", "STATUS", "TYPE");
    printf("|-----|----------------------|-----|-----------------|-----------------|\n");
	while (ptr != NULL)
	{
		printf("| %-3d | %-20s | %-3d | %-15s | %-15s |\n", i, ptr->data, ft_strlen(ptr->data), s[ptr->status], s[ptr->type]);
		printf("|-----|----------------------|-----|-----------------|-----------------|\n");
		ptr = ptr->next;
		i++;
	}
}

int is_type_word(char c, enum t_status status)
{
	if ((!ft_isspace(c) && c != S_QUOTE && c != D_QUOTE && c != PIPE && 
		c != DOLLAR && c != REDIRECT_IN && c != REDIRECT_OUT && c) || (c == S_QUOTE 
			&& status == IN_D_QUOTE) || (c == D_QUOTE && status == IN_S_QUOTE))
				return (1);
	return (0);
}

enum t_status change_status(char c, enum t_status status)
{
	if (c == S_QUOTE && status != IN_S_QUOTE)
		status = IN_S_QUOTE;
	else if (c == S_QUOTE && status == IN_S_QUOTE)
		status = GENERAL;
	if (c == D_QUOTE && status != IN_D_QUOTE)
		status = IN_D_QUOTE;
	else if (c == D_QUOTE && status == IN_D_QUOTE)
		status = GENERAL;
	return (status);
}

/* t_token_list *append_redir(t_token_list *token_list, char actual, char next, enum t_status status)
{
	if (actual == REDIRECT_IN)
	{
		if (next != REDIRECT_IN)
			token_list = append_char_token(token_list, actual, status, REDIR_IN);
		else if (next == REDIRECT_IN)
		{
			token_list = append_str_token(token_list, "<<", status, HERE_DOC);
			line ++;
		}
	}
	else if (actual == REDIRECT_OUT)
	{
		if (actual!= REDIRECT_OUT)
				token_list = append_char_token(token_list, *line, status, REDIR_OUT);
			else if (*(line + 1) == REDIRECT_OUT)	
			{
				token_list = append_str_token(token_list, ">>", status, D_REDIR_OUT);
				line ++;
			}
	}
} */
