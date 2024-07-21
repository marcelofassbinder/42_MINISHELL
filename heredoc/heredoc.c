/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:13:32 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/21 15:46:39 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_here_doc(char *line, t_shell *shell)
{
	char *after_doll;
	char *to_expand;
	char *to_free;
	char *copy_line;
	char *expanded;
	int	flag;
	int i;

	copy_line = ft_strdup(line);
	to_free = copy_line;
	while (ft_strchr(copy_line, DOLLAR))
	{
		flag = 0;
		i = 0;
		while(*copy_line != DOLLAR)
			copy_line++;
		copy_line++;
		while(copy_line[i] != ' ' && copy_line[i] != '\n' && copy_line[i] != S_QTE  && copy_line[i] != D_QTE)
			i++;
		if (i == 0)
			line = replace_expanded_var(line, to_expand, expanded, shell, 1);	
		else
		{
			after_doll = ft_substr(copy_line, 0, i);
			expanded = NULL;
			to_expand = ft_strdup(after_doll);
			expanded = expand(to_expand, shell);
			line = replace_expanded_var(line, after_doll, expanded, shell, 0);
		}
	}
	free(to_free);
	return(line);
}

char	*replace_expanded_var(char *line, char *after_doll, char *expanded, t_shell *shell, int flag)
{
	char *new_line;
	int	len;

	if (flag == 1)
		return(line);
	if (expanded)
		len = ft_strlen(line) + ft_strlen(expanded) - ft_strlen(after_doll) + 2;
	else
		len = ft_strlen(line) - ft_strlen(after_doll) + 2;
	new_line = ft_calloc(sizeof(char), len);
	if (!new_line)
		shell_error(shell, "Calloc Error: here_doc expansion", 0, true);
	new_line = copy_before_doll(line, after_doll, expanded, shell);
	if (expanded)
		new_line = ft_strjoin(new_line, expanded);		
	new_line = copy_after_doll(new_line, line, after_doll);
	free(after_doll);
	free(expanded);
	free(line);
	return(new_line);
}

char *copy_after_doll(char *new_line, char *line, char *after_doll)
{
	int j;
	int i;
	int copy;

	i = 0;
	while(line[i])
	{
		if (line[i] == DOLLAR && line[i + 1] == after_doll[0])
		{
			i++;
			j = 0;
			while(line[i] == after_doll[j])
			{
				i++;
				j++;
			}
			if (j == ft_strlen(after_doll))
				copy = i;
		}
		i++;
	}
	new_line = ft_strjoin(new_line, &line[copy]);
	return(new_line);
}

char *copy_before_doll(char *line, char *after_doll, char *expanded, t_shell *shell)
{
	char	*new;
	int		i;
	int		j;
	int		copy;

	copy = 0;
	new = ft_calloc(sizeof(char), ft_strlen(line) - ft_strlen(after_doll));
	if (!new)
		shell_error(shell, "Calloc Error : here_doc expansion", 0, true);
	i = 0;
	while(line[i])
	{
		if (line[i] == DOLLAR && line[i + 1] == after_doll[0])
		{
			i++;
			j = 0;
			while(line[i] == after_doll[j])
			{
				i++;
				j++;
			}
			if (j == ft_strlen(after_doll))
				copy = i - j;
		}
		i++;
	}
	i = 0;
	if (!expanded || !ft_strcmp(expanded, ""))
		copy--;
	while(i < copy)
	{
		if (line[i] == DOLLAR && line[i + 1] != ' ' && line[i + 1] != '\n')
			i++;
		new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
