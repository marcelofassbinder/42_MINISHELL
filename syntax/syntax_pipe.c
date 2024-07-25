/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:11:58 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/25 22:46:27 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	first_pipe(char *str)
{
	str = str - 2;
	while (*str)
	{
		if (!ft_isspace(*str))
			return (false);
		str--;
	}
	return (true);
}

bool	check_pipe(char *str)
{
	str++;
	if (empty_line(str) || exceeded_token(str, PIPE)
		|| previous_is_redir(str) || first_pipe(str))
	{
		ft_printf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `|'\n");
		return (true);
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
		if (*str == PIPE && status == GENERAL)
		{
			if (check_pipe(str))
				return (true);
		}
		str++;
	}
	return (false);
}
