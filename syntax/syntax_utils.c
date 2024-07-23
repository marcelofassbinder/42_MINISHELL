/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:21:43 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/23 16:41:05 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	special_char(char *str)
{
	char	*special = "();!&#*\\";
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
		if (ft_strchr(special, *str) && status == GENERAL)
		{
			ft_printf(STDERR_FILENO,
				"minishell: syntax error unexpected token `%c'\n", *str);
			return (true);
		}
		str++;
	}
	return (false);	
}

bool	unclosed_quotes(char *str)
{
	bool	flag;
	char	to_find;

	flag = false;
	while (*str)
	{
		if (*str == S_QTE || *str == D_QTE)
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

bool	previous_is_redir(char *str)
{
	str = str - 2;
	if (*str == R_OUT && *(str - 1) != R_OUT)
		return (false);
	while (str)
	{
		if (*str == R_OUT)
			return (true);
		else if (!ft_isspace(*str))
			return (false);
		str--;
	}
	return (false);
}

bool	empty_line(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
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
		if (!ft_isspace(*str))
			break ;
		str++;
	}
	return (false);
}