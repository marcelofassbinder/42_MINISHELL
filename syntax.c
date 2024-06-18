/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:31:30 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/18 12:49:47 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


bool	unclosed_quotes(char *line)
{
	
}

bool	check_syntax(char *line)
{
	if (!unclosed_quotes(line))
		return false;
	return true;
}