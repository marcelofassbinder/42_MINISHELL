/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:31:30 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/25 14:48:20 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	check_redir(char *str)
{
	char	redir_type;

	redir_type = *str;
	str++;
	if (*str == redir_type)
		str++;
	if (exceeded_token(str, redir_type) || empty_line(str))
	{
		ft_printf(STDERR_FILENO,
		"minishell: syntax error unexpected token '%c'\n",
		redir_type);
		return (true);
	}
	return (false);
}

bool	check_pipe(char *str)
{
	str++;
	if (empty_line(str) || exceeded_token(str, '|') || previous_is_redir(str))
	{
		ft_printf(STDERR_FILENO,
		"minishell: syntax error unexpected token |\n");
		return (true);
	}
	return (false);
}

bool	redir_error(char *str)
{
	enum 	e_status	status;	

	status = GENERAL;
	while (*str)
	{
		if (*str == D_QTE && status == GENERAL)
			status = IN_D_QUOTE;
		else if (*str == S_QTE && status == GENERAL)
			status = IN_S_QUOTE;
		else if (*str == S_QTE && status == IN_S_QUOTE)
			status = GENERAL;
		else if (*str == D_QTE && status == IN_D_QUOTE)
			status = GENERAL;
		if ((*str == '>' || *str == '<') && (status == GENERAL))
		{
			if (check_redir(str))
				return (true);
			else
				str++;
		}
		else
			str++;
	}
	return (false);
}

bool	pipe_error(char *str)
{
	enum e_status	status;

	status = GENERAL;
	while (*str)
	{
		if (*str == D_QTE && status == GENERAL)
			status = IN_D_QUOTE;
		else if (*str == S_QTE && status == GENERAL)
			status = IN_S_QUOTE;
		else if (*str == S_QTE && status == IN_S_QUOTE)
			status = GENERAL;
		else if (*str == D_QTE && status == IN_D_QUOTE)
			status = GENERAL;
		if (*str == '|' && status == GENERAL)
		{
			if (check_pipe(str))
				return (true);
		}
		str++;
	}
	return (false);
}

bool	check_syntax(char *line)
{
	if (unclosed_quotes(line))
		return (false);
	if (redir_error(line))
		return (false);
	if (pipe_error(line))
		return (false);
	return (true);
}
