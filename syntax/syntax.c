/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:31:30 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/26 15:37:47 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_redir(char *str)
{
	char	redir_type;
	char	*save_str;

	redir_type = *str;
	str++;
	if (*str == redir_type)
		str++;
	save_str = str;
	if (empty_line(str))
	{
		ft_printf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `newline'\n");
		return (true);
	}
	str = save_str;
	if (exceeded_token(str, redir_type))
	{
		ft_printf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `%c'\n", redir_type);
		return (true);
	}
	return (false);
}

bool	redir_error(char *str)
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
		if ((*str == R_OUT || *str == R_IN) && (status == GENERAL))
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

bool	check_syntax(char *line)
{
	if (unclosed_quotes(line))
		return (false);
	else if (redir_error(line))
		return (false);
	else if (pipe_error(line))
		return (false);
	else if (special_char(line))
		return (false);
	return (true);
}
