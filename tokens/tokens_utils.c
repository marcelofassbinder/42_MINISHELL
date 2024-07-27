/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:50:22 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/27 20:37:43 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prepare_tokens(t_token_list *token_list, t_shell *shell)
{
	join_spaces(token_list);
	check_dollar(token_list, shell, token_list->first);
	g_received_signal = 0;
	join_quotes(token_list);
	join_words(token_list);
	find_files(token_list);
	token_redir_pipe(token_list);
}

t_token	*get_eof_status(t_token *tmp)
{
	if (tmp->status != GENERAL || tmp->next->status != GENERAL)
		tmp->status = IN_S_QUOTE;
	return (tmp);
}

int	is_type_word(char c)
{
	if (!ft_isspace(c) && c != S_QTE && c != D_QTE && c != PIPE
		&& c != DOLLAR && c != R_IN && c != R_OUT && c)
		return (1);
	return (0);
}

bool	is_redir(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == D_REDIR_OUT || token->type == HERE_DOC)
		return (true);
	return (false);
}

enum e_status	append_quotes(t_token_list *token_list, char c,
	enum e_status status)
{
	if (c == S_QTE)
		status = change_status(token_list, c, status, S_QUOTE);
	else if (c == D_QTE)
		status = change_status(token_list, c, status, D_QUOTE);
	return (status);
}
