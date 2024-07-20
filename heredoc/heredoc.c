/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:13:32 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/20 20:47:59 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/* 
char	*expand_here_doc(char *line, t_shell *shell)
{
	char *after_doll;
	char *to_expand;
	char *expanded;
	int	flag;
	
	while (after_doll && (after_doll[0] != ' ' && after_doll[0] != '\n'))
	{
		flag = 0;
		if (after_doll)
		{
			if (after_doll[0] == ' ' || after_doll[0] == '\n')
				flag = 1;
			after_doll = clean_var(after_doll);
			if (!after_doll)
				shell_error(shell, "Calloc Error: here_doc expansion", 0, true);
			expanded = NULL;
			to_expand = ft_strdup(after_doll);
			expanded = expand(after_doll, shell);
			line = replace_expanded_var(line, to_expand, expanded, shell, flag);
		}
	}
	return(line);
}
 */
char	*expand_here_doc(char *line, t_shell *shell)
{
	char *after_doll;
	char *to_expand;
	char *copy_line;
	char *expanded;
	int	flag;
	int i;

	copy_line = ft_strdup(line);
	while (ft_strchr(copy_line, DOLLAR))
	{
		flag = 0;
		i = 0;
		while(*copy_line != DOLLAR)
			copy_line++;
		copy_line++;
		while(copy_line[i] != ' ' && copy_line[i] != '\n')
			i++;
		if (i == 0)
			line = replace_expanded_var(line, to_expand, expanded, shell, 1);	
		else
		{
			after_doll = ft_substr(copy_line, 0, i);
			expanded = NULL;
			to_expand = ft_strdup(after_doll);
			expanded = expand(after_doll, shell);
			line = replace_expanded_var(line, to_expand, expanded, shell, 0);
		}
	}
	return(line);
}


char	*clean_var(char *after_doll)
{
	int i;

	if (after_doll)
	{
		i = 0;
		while(after_doll[i] && after_doll[i] != ' ' && after_doll[i] != '\n' && after_doll[i] != S_QTE && after_doll[i] != D_QTE && after_doll[i] != DOLLAR)
			i++;
		return(ft_substr(after_doll, 0, i));
	}
	return (NULL);
}

char	*replace_expanded_var(char *line, char *after_doll, char *expanded, t_shell *shell, int flag)
{
	char *new_line;
	int	len;
	int	i;
	int	j;
	int	k;

	if (flag == 1)
		return(line);
	if (expanded[0])
		len = ft_strlen(line) + ft_strlen(expanded) - ft_strlen(after_doll) + 2;
	else
		len = ft_strlen(line) - ft_strlen(after_doll) + 2;
	new_line = ft_calloc(sizeof(char), len);
	if (!new_line)
		shell_error(shell, "Calloc Error: here_doc expansion", 0, true);
	i = 0;
	while(line[i] != DOLLAR)
	{
		new_line[i] = line[i];
		i++;
	}
	/* if (flag == 1)
		new_line[i++] = DOLLAR; */
	k = i;
	if (expanded)
	{
		j = 0;
		while(expanded[j])
			new_line[i++] = expanded[j++];
	}
	while(line[k + ft_strlen(after_doll) + 1])
		new_line[i++] = line[k++ + ft_strlen(after_doll) + 1];
	//free(line);
	return(new_line);
}

//char *copy_before_doll(char *line, char *after_doll)
