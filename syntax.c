/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:31:30 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/24 18:42:14 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	unclosed_quotes(char *str)
{
	bool	flag;
	char	to_find;

	flag = false;
	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			to_find = *str;
			str++;
			flag = true;
			while (*str && *str != to_find)
				str++;
			if (*str == to_find)
				flag = false;
		}
		if (*str)
			str++;
	}
	if (flag == true)
		ft_printf (STDERR_FILENO, "minishell: syntax error unclosed quotes\n");
	return (flag);
}

bool	empty_line(char *str)
{
	while (*str)
	{
		if (!(*str >= 9 || *str <= 13) || *str != 32)
			return (false);
		str++;
	}
	return (true);
}

bool	exceeded_token(char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (true);
		if (!(*str >= 9 || *str <= 13) || *str != 32)
			break ;
		str++;
	}
	return (false);
}

bool	redir_error(char *str)
{
	char	redir_type;

	while (*str)
	{
		if (*str == '>' || *str == '<')
		{
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
		}
		else
			str++;
	}
	return (false);
}

bool	previous_is_redir(char *str)
{
	str = str - 2;
	if (*str == '>' && *(str - 1) != '>')
		return (false);
	while (str)
	{
		if (*str == '>')
			return (true);
		else if ((*str  < 9 || *str > 13) && *str != 32)
			return (false);
		str--;
	}
	return (false);
}

bool	pipe_error(char *str)
{
	while (*str)
	{
		if (*str == '|')
		{
			str++;
			if (empty_line(str) || exceeded_token(str, '|') || previous_is_redir(str))
			{
				ft_printf(STDERR_FILENO,
					"minishell: syntax error unexpected token |\n");
				return (true);
			}
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
