/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:48:24 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/18 19:13:51 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	tokenizer(char *line)
{
	t_token_list *token_list;
	int 	i;
	int 	status;
	int 	old_status;
	int 	word_len;
	char 	*word;

	token_list = ft_calloc(sizeof(t_token_list), 1);
	i = 0;
	status = 0;
	old_status = 0;
	while(*line)
	{
		if (!ft_isspace(*line) && *line != S_QUOTE && *line != D_QUOTE && *line != PIPE && *line != ENV && *line != REDIR_IN && *line != REDIR_OUT)
		{
			word = line;
			word_len = 0;
			while (!ft_isspace(*line) && *line != S_QUOTE && *line != D_QUOTE && *line != PIPE && *line != ENV && *line != REDIR_IN && *line != REDIR_OUT && *line)
			{
				line++;
				word_len++;
			}
			token_list = append_str_token(token_list, ft_substr(word, 0, word_len), status, 4);
		}	
		if (*line == S_QUOTE && status != 1)
			status = 1;
		else if (*line == S_QUOTE && status == 1)
			status = 0;
		if (*line == D_QUOTE && status != 2)
			status = 2;
		else if (*line == D_QUOTE && status == 2)
			status = 0;
		if (ft_isspace(*line))
			token_list = append_char_token(token_list, *line, status, 3);
		if (*line == PIPE)
			token_list = append_char_token(token_list, *line, status, 5);
		if (*line == ENV)
			token_list = append_char_token(token_list, *line, status, 6);
		if (*line == REDIR_IN)
		{
			if (*(line + 1) != REDIR_IN)
				token_list = append_char_token(token_list, *line, status, 7);
			else if (*(line + 1) == REDIR_IN)
			{
				token_list = append_str_token(token_list, "<<", status, 10);
				line ++;
			}
		}
		if (*line == REDIR_OUT)
		{
			if (*(line + 1) != REDIR_OUT)
				token_list = append_char_token(token_list, *line, status, 8);
			else if (*(line + 1) == REDIR_OUT)	
			{
				token_list = append_str_token(token_list, ">>", status, 9);
				line ++;
			}
		}
		line++;
	}
	print_token_list(token_list);

}

t_token_list *append_str_token(t_token_list *token_list, char *str, int status, int type)
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

t_token_list *append_char_token(t_token_list *token_list, char c, int status, int type)
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
	char *s[] = {"general", "in_s_quote", "in_d_quote", "w_space", "word", "pipeline", "env", "redir_in", "redir_out", "d_redir_out", "here_doc"};

	ptr = token_list->first;
	i = 1;
	printf("| %-3s | %-20s | %-15s | %-15s |\n", "ID", "TOKEN", "STATUS", "TYPE");
    printf("|-----|----------------------|-----------------|-----------------|\n");
	while (ptr != NULL)
	{
		printf("| %-3d | %-20s | %-15s | %-15s |\n", i, ptr->data, s[ptr->status], s[ptr->type]);
		ptr = ptr->next;
		i++;
	}

}