/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:13:32 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/24 16:31:46 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_here_doc(char *line, t_shell *shell)
{
	char *after_doll;
	char *to_free;
	char *copy_line;
	int i;

	copy_line = ft_strdup(line);
	to_free = copy_line;
	while (ft_strchr(copy_line, DOLLAR))
	{
		i = 0;
		while(*copy_line != DOLLAR)
			copy_line++;
		copy_line++;
		while(copy_line[i] != ' ' && copy_line[i] != '\n' && copy_line[i] != S_QTE  && copy_line[i] != D_QTE)
			i++;
		if (i == 0)	
			continue ;
		after_doll = ft_substr(copy_line, 0, i);
		line = replace_expanded_var(line, after_doll, shell);
		copy_line = line;
	}
	free(to_free);
	return(line);
}

char	*replace_expanded_var(char *line, char *after_doll, t_shell *shell)
{
	char *new_line;
	char *to_expand;
	char *expanded;

	to_expand = ft_strdup(after_doll);
	expanded = expand(to_expand, shell);
	new_line = copy_before_doll(line, after_doll, shell);
	if (expanded)
		new_line = ft_strjoin(new_line, expanded);		
	new_line = copy_after_doll(new_line, line, after_doll);
	free(after_doll);
	free(expanded);
	free(line);
	return(new_line);
}

char *copy_before_doll(char *line, char *after_doll, t_shell *shell)
{
	char	*new;
	int		start;
	int		len;

	start = 0;
	while(line[start] != DOLLAR ||
		ft_strncmp(&line[start + 1], after_doll, ft_strlen(after_doll)))
		start ++;
	len = start;
	new = ft_substr(line, 0, len);
	if (!new)
		shell_error(shell, "Calloc Error: expansion in heredoc", 0, true);
	return (new);
}

char *copy_after_doll(char *new_line, char *line, char *after_doll)
{
	int start;

	start = 0;
	while(line[start] != DOLLAR ||
		ft_strncmp(&line[start + 1], after_doll, ft_strlen(after_doll)))
		start ++;
	start += ft_strlen(after_doll) + 1;
	new_line = ft_strjoin(new_line, &line[start]);
	return(new_line);
}
